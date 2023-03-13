#pragma once

#include "CoreMinimal.h"
#include "CoreEnums.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

class ACCharacter_Base;
class UWeaponAsset;
class UWeapon;

DECLARE_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, EWeaponType)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnComboEnable, bool)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCWeaponComponent();
protected:
	virtual void BeginPlay() override;
	
public:
	void ChangeWeapon(int const& Index);

	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<UWeaponAsset*> WeaponAssets;
	UPROPERTY()
		TArray<UWeapon*> Weapons;
	
public:
	FWeaponTypeChanged OnWeaponTypeChanged;
	FOnComboEnable OnComboEnable;
	
private:
	ACCharacter_Base* OwnerCharacter;
	UWeapon* CurrWeapon;
};
