#include "Abilities/CAbilityType.h"
#include "Components/CAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

//  ******************************
//      Effect Container
//  ******************************

FCGameplayEffectContainer::FCGameplayEffectContainer() 
{

}

FCGameplayEffectContainerSpec::FCGameplayEffectContainerSpec()
{

}

//  ******************************
//      Effect Container Spec
//  ******************************
bool FCGameplayEffectContainerSpec::HasValidEffects() const
{
	return TargetGameplayEffectSpecs.Num() > 0;
}

bool FCGameplayEffectContainerSpec::HasValidTargets() const
{
	return TargetData.Num() > 0;
}

//?? Ÿ?? ?߰?
void FCGameplayEffectContainerSpec::AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors)
{
	for (const FHitResult& HitResult : HitResults)
	{
		FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
		TargetData.Add(NewData);
	}

	if (TargetActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
		NewData->TargetActorArray.Append(TargetActors);
		TargetData.Add(NewData);
	}
}