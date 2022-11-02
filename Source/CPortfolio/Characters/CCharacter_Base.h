#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "Abilities/CGameplayAbility.h"

#include "CCharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACCharacter_Base*, Character);
UCLASS()
class CPORTFOLIO_API ACCharacter_Base : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	friend class UCAttributeSet;

//  *********************
//      扁夯 技泼
//  *********************
public:
	ACCharacter_Base();
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void Tick(float DeltaTime) override;


//  *********************
//      Movement 贸府
//  *********************
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		bool IsInAir;
public:
	bool GetIsInAir();
	void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode) override;


//  *********************
//      Evade 贸府
//  *********************	
public:
	UFUNCTION(Category = "Evade")
		virtual void BeginEvade() {}
	UFUNCTION(Category = "Evade")
		virtual void EndEvade() {}


//  *********************
//		Attribute 贸府
//  *********************
public:
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetCurrHP() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetMaxHP() const;
	UFUNCTION(BlueprintCallable, Category = "Attribute")
		float GetMoveSpeed() const;
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnDamaged(float InAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACCharacter_Base* InstigatorCharacter, AActor* DamageCauser);
	UFUNCTION(BlueprintImplementableEvent)
		void OnHPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	UFUNCTION(BlueprintImplementableEvent)
		void OnMoveSpeedChanged(float InAmount, const struct FGameplayTagContainer& EventTags);


protected:
	virtual void HandleDamage(float InAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACCharacter_Base* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float InAmount, const struct FGameplayTagContainer& EventTags);

protected:		
	UPROPERTY(VisibleDefaultsOnly, Category = "Attribute")
		class UCAttributeSet* AttributeSet;

//  *********************
//      Ability 贸府
//  *********************
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Ability")
		class UCAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = "Ability")
		TArray<TSubclassOf<class UCGameplayAbility>> GameplayAbilities;
	UPROPERTY(VisibleDefaultsOnly, Category = "Ability")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	UPROPERTY(VisibleDefaultsOnly, Category = "Ability")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

protected:
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<class UCGameplayAbility*>& ActiveAbilities);
	

protected:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void AddStartupGameplayAbilities();
	virtual void AddCharacterAbilities();
	virtual void RemoveStartupGameplayAbilities();
	bool ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation = true);

protected:
	bool bAbilitiesInitialized;

//  *********************
//      荤噶 贸府
//  *********************

public:
	virtual void CharacterDie();

public:
	UFUNCTION(BlueprintCallable, Category = "Character")
		virtual void EndDying();

public:
	UPROPERTY(BlueprintAssignable, Category = "Character")
		FCharacterDiedDelegate OnCharacterDied;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Animation")
		class UAnimMontage* DeathMontage;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* Weapon;
};
