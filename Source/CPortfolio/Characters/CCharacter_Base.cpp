#include "Characters/CCharacter_Base.h"
#include "Global.h"


#include "Attributes/CAttributeSet.h"
#include "Components/CAbilitySystemComponent.h"
#include "Components/CWeaponComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


//  *********************
//      扁夯 技泼
//  *********************
ACCharacter_Base::ACCharacter_Base()
{
	IsInAir = false;

	CHelpers::CreateActorComponent<UCAbilitySystemComponent>(this, &AbilitySystemComponent, "AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	CHelpers::CreateActorComponent<UCAttributeSet>(this, &AttributeSet, "AttributeSet");
	bAbilitiesInitialized = false;
}

void ACCharacter_Base::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Initialize
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}
void ACCharacter_Base::UnPossessed()
{
	
}

void ACCharacter_Base::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (AbilitySystemComponent)
		AbilitySystemComponent->RefreshAbilityActorInfo();
}

void ACCharacter_Base::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ACCharacter_Base, 1);
}

//  *********************
//      Movement 贸府
//  *********************

bool ACCharacter_Base::GetIsInAir()
{
	return IsInAir;
}

void ACCharacter_Base::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PrevCustomMode);
	EMovementMode NewMovementMode = GetCharacterMovement()->MovementMode;

	switch (NewMovementMode)
	{
		case EMovementMode::MOVE_Walking : 
		case EMovementMode::MOVE_NavWalking :
		{
			IsInAir = false;
			break;
		}

		case EMovementMode::MOVE_Falling :
		case EMovementMode::MOVE_Flying :
		{
			IsInAir = true;
			break;
		}
	}
	if(IsInAir)
		CLog::Print("In Air");
	else
		CLog::Print("On Ground");
}


//  *********************
//      Evade 贸府
//  *********************	


//  *********************
//		Attribute 贸府
//  *********************
float ACCharacter_Base::GetCurrHP() const
{
	if(!!AttributeSet)
		return AttributeSet->GetCurrHP();
	return 1.0f;
}

float ACCharacter_Base::GetMaxHP() const
{
	if(!!AttributeSet)
		return AttributeSet->GetMaxHP();
	return 0.0f;
}

float ACCharacter_Base::GetMoveSpeed() const
{
	if(!!AttributeSet)
		return AttributeSet->GetMoveSpeed();
	return 0.0f;
}

void ACCharacter_Base::HandleDamage(float InAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACCharacter_Base* InstigatorCharacter, AActor* DamageCauser)
{
	OnDamaged(InAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);	
}

void ACCharacter_Base::HandleHPChanged(float InAmount, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
		OnHPChanged(InAmount, EventTags);
}

void ACCharacter_Base::HandleMPChanged(float InAmount, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
		OnMPChanged(InAmount, EventTags);
}

void ACCharacter_Base::HandleMoveSpeedChanged(float InAmount, const struct FGameplayTagContainer& EventTags)
{
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	if (bAbilitiesInitialized)
		OnMoveSpeedChanged(InAmount, EventTags);
}


//  *********************
//      Ability 贸府
//  *********************

void ACCharacter_Base::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UCGameplayAbility*>& ActiveAbilities)
{
	CheckNull(AbilitySystemComponent);
	AbilitySystemComponent->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
}

UAbilitySystemComponent* ACCharacter_Base::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ACCharacter_Base::AddStartupGameplayAbilities()
{
	CheckNull(AbilitySystemComponent);
	if(bAbilitiesInitialized)
		return;
	if (GetLocalRole() != ROLE_Authority)
		return;

	for (TSubclassOf<UCGameplayAbility>& StartupAbility : GameplayAbilities)
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));

	 // Now apply passives
	for (TSubclassOf<UGameplayEffect>& GameplayEffect : StartupEffects)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	} 

	//AddSlottedGameplayAbilities();

	bAbilitiesInitialized = true;
}


void ACCharacter_Base::RemoveStartupGameplayAbilities()
{
	CheckNull(AbilitySystemComponent);
	if(GetLocalRole() != ROLE_Authority)
		return;
	if(!bAbilitiesInitialized)
		return;

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && GameplayAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);

	FGameplayEffectQuery Query;
	Query.EffectSource = this;
	AbilitySystemComponent->RemoveActiveEffects(Query);

	//RemoveSlottedGameplayAbilities(true);

	bAbilitiesInitialized = false;
}

//  *********************
//      Equip 贸府
//  *********************
void ACCharacter_Base::Equip(uint8 const& InNumber) {}
void ACCharacter_Base::EndEquip() {}
void ACCharacter_Base::UnEquip() {}

//  *********************
//      荤噶 贸府
//  *********************
void ACCharacter_Base::CharacterDie()
{
	//RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0.0f;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if(!!AbilitySystemComponent)
		AbilitySystemComponent->CancelAbilities();
	if(!!DeathMontage)
		PlayAnimMontage(DeathMontage);
	else
		EndDying();
}

void ACCharacter_Base::EndDying()
{
	Destroy();
}





