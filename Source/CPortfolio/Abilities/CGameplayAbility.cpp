#include "CGameplayAbility.h"
#include "Global.h"

#include "Components/CAbilitySystemComponent.h"

UCGameplayAbility::UCGameplayAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    if(bActivateAbilityGranted)
    {
        ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
    }
}