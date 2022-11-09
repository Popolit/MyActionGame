#include "CTargetType.h"

#include "Characters/CCharacter_Base.h"

//  ******************************
//      Target Type
//  ******************************

UCTargetType::UCTargetType()
{

}

void UCTargetType::GetTargets_Implementation(class ACCharacter_Base* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	return;
}

//  ******************************
//      Target Type UseOwner
//  ******************************

UCTargetType_UseOwner::UCTargetType_UseOwner()
{

}

void UCTargetType_UseOwner::GetTargets_Implementation(ACCharacter_Base* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	OutActors.Add(TargetingCharacter);
}

//  ******************************
//      Target Type UseEventData
//  ******************************

UCTargetType_UseEventData::UCTargetType_UseEventData()
{

}

void UCTargetType_UseEventData::GetTargets_Implementation(ACCharacter_Base* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
	const FHitResult* FoundHitResult = EventData.ContextHandle.GetHitResult();
	if (FoundHitResult)
		OutHitResults.Add(*FoundHitResult);
	else if (EventData.Target)
		OutActors.Add(const_cast<AActor*>(EventData.Target));
}