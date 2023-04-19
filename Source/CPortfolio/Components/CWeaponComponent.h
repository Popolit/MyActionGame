#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/CI_EventHandler.h"
#include "CWeaponComponent.generated.h"

class ACCharacter_Base;
class UWeaponAsset;
class UWeapon;
class AWeaponAttachment;

//PrevWeapon, NewWeapon
DECLARE_MULTICAST_DELEGATE_TwoParams(FWeaponChanged, UWeapon*, UWeapon*)
DECLARE_DELEGATE_TwoParams(FOnFABRIKWeapon, bool, AWeaponAttachment*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnComboEnable, bool)


/* Weapon Component */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCWeaponComponent();
	virtual void BeginPlay() override;
	
public:
	void ChangeWeapon(int const& Index);
	void BindWeaponEvent(FName const& InEventName, ICI_EventHandler* InEventHandler);
	void OnWeaponEvent(FName const& InEventName);

public:
	FORCEINLINE UWeapon* GetWeapon() const { return CurrWeapon; }
	FORCEINLINE UWeapon* GetPrevWeapon() const { return PrevWeapon; }

private:
	void CheckWeaponHasFABRIK();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<UWeaponAsset*> WeaponAssets;
	UPROPERTY()
		TArray<UWeapon*> Weapons;	//0 = Unarmed or Default Weapon
	
public:
	FWeaponChanged OnWeaponChanged;
	FOnFABRIKWeapon OnFABRIKWeapon;
	FOnComboEnable OnComboEnable;
	
private:
	ACCharacter_Base* OwnerCharacter;
	TMap<FName, UObject*> WeaponEvents;
	UWeapon* CurrWeapon;
	UWeapon* PrevWeapon;
};
