#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "Abilities/CGameplayAbility.h"

#include "CCharacter_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACCharacter_Base*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumped);
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
	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* WeaponComponent;
	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* ActionComponent;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComponent;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;
	UPROPERTY(VisibleDefaultsOnly)
		class UCFeetComponent* FeetComponent;

//  *********************
//      Movement 贸府
//  *********************
public:
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode) override;
	virtual void OnJumped_Implementation() override;

public:
	FOnJumped OnJumped;


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
		void OnMPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	UFUNCTION(BlueprintImplementableEvent)
		void OnMoveSpeedChanged(float InAmount, const struct FGameplayTagContainer& EventTags);


protected:
	virtual void HandleDamage(float InAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ACCharacter_Base* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMPChanged(float InAmount, const struct FGameplayTagContainer& EventTags);
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
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

protected:
	UFUNCTION(BlueprintCallable, Category = "Ability")
		void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<class UCGameplayAbility*>& ActiveAbilities);
	

protected:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void AddStartupGameplayAbilities();
	virtual void RemoveStartupGameplayAbilities();
	bool ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation = true);

protected:
	bool bAbilitiesInitialized;

//  *********************
//      Equip 贸府
//  *********************
protected:
	UFUNCTION(Category = "Equip")
		virtual void ChangeWeapon(uint8 const& InNumber = 0);
	
//  *********************
//      单固瘤 贸府
//  *********************
public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
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

};

