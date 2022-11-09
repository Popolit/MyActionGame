#include "CAttributeSet.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UCAttributeSet::UCAttributeSet() 
    : MaxHP(1.0f)
    , CurrHP(1.0f)
	, MaxMP(0.0f)
    , CurrMP(0.0f)
    , TickIncMPAmount(0.0f)
    , MoveSpeed(400.0f)
    , Damage(0.0f)
{

}


//  *********************
//      Attribute 처리
//  *********************

void UCAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

//value 수정 전에 검토할 사항
void UCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHPAttribute())
		AdjustAttributeForMaxChange(CurrHP, MaxHP, NewValue, GetCurrHPAttribute());
	else if (Attribute == GetMaxMPAttribute())
		AdjustAttributeForMaxChange(CurrMP, MaxMP, NewValue, GetCurrMPAttribute());
}

//value 수정 후에 검토할 사항, 클램핑/사망 처리 등
void UCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	//DeltaValue 구하기
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
		DeltaValue = Data.EvaluatedData.Magnitude;

	//Owner 액터, 컨트롤러 구하기
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ACCharacter_Base* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ACCharacter_Base>(TargetActor);
	}

    //데미지일 경우
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		//소스 액터, 컨트롤러 구하기
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		ACCharacter_Base* SourceCharacter = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
					SourceController = Pawn->GetController();
			}

			//소스가 폰인지 액터인지 판단
			if (SourceController)
				SourceCharacter = Cast<ACCharacter_Base>(SourceController->GetPawn());
			else
				SourceCharacter = Cast<ACCharacter_Base>(SourceActor);

			//Causer 액터 구하기
			if (Context.GetEffectCauser())
				SourceActor = Context.GetEffectCauser();
		}

		//Hitresult 구하기
		FHitResult HitResult;
		if (Context.GetHitResult())
			HitResult = *Context.GetHitResult();

		// 데미지 구하기
		const float LocalDamage = GetDamage();
		SetDamage(0.f);

		if (LocalDamage > 0)
		{
			// Apply the HP change and then clamp it
			const float OldHP = GetCurrHP();
			SetCurrHP(FMath::Clamp(OldHP - LocalDamage, 0.0f, GetMaxHP()));

			if (TargetCharacter)
			{
				TargetCharacter->HandleDamage(LocalDamage, HitResult, SourceTags, SourceCharacter, SourceActor);
				TargetCharacter->HandleHPChanged(-LocalDamage, SourceTags);
			}
		}
        return;
	}

    //HP일 경우
	if (Data.EvaluatedData.Attribute == GetCurrHPAttribute())
	{
		//HP를 0~MAX 사이의 값으로 변경
		SetCurrHP(FMath::Clamp(GetCurrHP(), 0.0f, GetMaxHP()));

		if (TargetCharacter)
			TargetCharacter->HandleHPChanged(DeltaValue, SourceTags);

        return;
	}
	if (Data.EvaluatedData.Attribute == GetCurrMPAttribute())
	{
		//MP를 0~MAX 사이의 값으로 변경
		SetCurrMP(FMath::Clamp(GetCurrMP(), 0.0f, GetMaxMP()));

		if (TargetCharacter)
			TargetCharacter->HandleMPChanged(DeltaValue, SourceTags);

		return;
	}
    //MoveSpeed일 경우
	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		if (TargetCharacter)
			TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
	}
}

void UCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{   
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UCAttributeSet, MaxHP);
    DOREPLIFETIME(UCAttributeSet, CurrHP);
    DOREPLIFETIME(UCAttributeSet, MaxMP);
    DOREPLIFETIME(UCAttributeSet, CurrMP);
    DOREPLIFETIME(UCAttributeSet, TickIncMPAmount);
    DOREPLIFETIME(UCAttributeSet, MoveSpeed);
}



//  *******************
//      레플리케이션
//  *******************
void UCAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, MaxHP, OldValue);
}
void UCAttributeSet::OnRep_CurrHP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, CurrHP, OldValue);
}
void UCAttributeSet::OnRep_MaxMP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, MaxMP, OldValue);
}
void UCAttributeSet::OnRep_CurrMP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, CurrMP, OldValue);
}
void UCAttributeSet::OnRep_TickIncMP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, TickIncMPAmount, OldValue);
}
void UCAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, MoveSpeed, OldValue);
}