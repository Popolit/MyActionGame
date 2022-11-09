#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/CWeaponStructure.h"
#include "CWeaponComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FWeaponChanged, TSubclassOf<class ACWeapon>, TSubclassOf<class ACWeapon>)

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
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TArray<TSubclassOf<class ACWeapon>> WeaponClasses;

private:
	UPROPERTY()
		class ACPlayer* Owner;
	TArray<ACWeapon*> WeaponList;

public:
	UFUNCTION()
		void ChangeWeaponType(TSubclassOf<ACWeapon> PrevType, TSubclassOf<ACWeapon> NewType);

public:
	UPROPERTY()
		ACWeapon* CurrWeapon;
	EWeaponType WeaponType;

//  *********************
//      Equip
//  *********************
public:
	UFUNCTION(Category="Equip")
		void Equip(uint8 const& Index);
	UFUNCTION(Category="Equip")
		void EndEquip() const;
	UFUNCTION(Category="Equip")
		void UnEquip() const;
	UFUNCTION(Category="Equip")
		void EndUnEquip();

public:
	FWeaponChanged OnWeaponChanged;
};
