#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/CWeapon.h"
#include "Weapons/CWeaponStructure.h"
#include "CWeaponComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, EWeaponType)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnComboEnable, bool)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

//  *********************
//      기본 세팅
//  *********************
public:	
	UCWeaponComponent();
protected:
	virtual void BeginPlay() override;

private:
	class ACCharacter_Base* OwnerCharacter;


//  *********************
//      Weapon Asset
//  *********************

public:
	class UCEquipment* GetEquipment();
	class UCEquipment* GetPrevEquipment();
	TArray<class ACAttachment*> const* GetAttachments();
	EWeaponType GetWeaponType(int const& Index);
	UCActionData* GetActionData();


private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		UCWeaponAsset* UnarmedAsset;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TArray<class UCWeaponAsset*> Weapons;
	UPROPERTY()
		TArray<class UCWeapon*> WeaponDatas;

private:
	TArray<EWeaponType> WeaponTypes;
	int CurrWeaponIndex;	//-1 = Unarmed
	int PrevWeaponIndex;

//  *********************
//      Equip
//  *********************
public:
	void ChangeWeapon(int const& Index);

private:
	void EquipWeapon();
	void UnEquipWeapon();

public:
	FWeaponTypeChanged OnWeaponTypeChanged;
	FOnComboEnable OnComboEnable;
};
