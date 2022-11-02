#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReceivedDamageDelegate, UCAbilitySystemComponent*, SourceASC, float, Amount);

UCLASS()
class CPORTFOLIO_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()		
public:
	UCAbilitySystemComponent();

public:
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<class UCGameplayAbility*>& ActiveAbilities);
};
