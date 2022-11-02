#include "CAttributeSet_Player.h"

#include "Characters/Player/CPlayer.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UCAttributeSet_Player::UCAttributeSet_Player()
{ 
    Super::Super();

}

void UCAttributeSet_Player::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
		DeltaValue = Data.EvaluatedData.Magnitude;

    const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
    
    AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ACPlayer* TargetCharacter = nullptr;

    //MP일 경우
    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ACPlayer>(TargetActor);
	}

}


//  *********************
//      레플리케이션
//  *********************
void UCAttributeSet_Player::OnRep_MaxMP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet_Player, MaxMP, OldValue);
}
void UCAttributeSet_Player::OnRep_CurrMP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet_Player, CurrMP, OldValue);
}
void UCAttributeSet_Player::OnRep_TickIncMP(const FGameplayAttributeData& OldValue)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet_Player, TickIncMPAmount, OldValue);
}