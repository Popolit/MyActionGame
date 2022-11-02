#include "CAbilitySystemComponent.h"

#include "Abilities/CGameplayAbility.h"

UCAbilitySystemComponent::UCAbilitySystemComponent()
{
}

void UCAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UCGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
			ActiveAbilities.Add(Cast<UCGameplayAbility>(ActiveAbility));
	}
}
