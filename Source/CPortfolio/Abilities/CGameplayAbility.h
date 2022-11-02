#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class AbilityID : uint8
{
	NONE,
	CONFIRM,
	CANCEL
};


UCLASS()
class CPORTFOLIO_API UCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
		AbilityID AbilityInputID = AbilityID::NONE;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
		AbilityID AbilityID = AbilityID::NONE;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
		bool bActivateAbilityGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
