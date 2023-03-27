#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

class ACCharacter_Base;
class UWeaponAsset;
class UWeapon;

DECLARE_MULTICAST_DELEGATE_TwoParams(FWeaponChanged, UWeapon*, UWeapon*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnComboEnable, bool)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCWeaponComponent();
	virtual void BeginPlay() override;
	
public:
	void ChangeWeapon(int const& Index);

public:
	FORCEINLINE const UWeapon* GetWeapon() const { return CurrWeapon; }
	FORCEINLINE const UWeapon* GetPrevWeapon() const { return PrevWeapon; }

	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<UWeaponAsset*> WeaponAssets;
	UPROPERTY()
		TArray<UWeapon*> Weapons;	//0 = Unarmed or Default Weapon
	
public:
	FWeaponChanged OnWeaponChanged;
	FOnComboEnable OnComboEnable;
	
private:
	ACCharacter_Base* OwnerCharacter;
	UWeapon* CurrWeapon;
	UWeapon* PrevWeapon;
};
