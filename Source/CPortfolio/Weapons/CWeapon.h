#pragma once

#include "CoreMinimal.h"
#include "CWeaponStructure.h"
#include "GameFramework/Actor.h"

#include "CWeapon.generated.h"



UCLASS()
class CPORTFOLIO_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
//  *********************
//      기본 세팅
//  *********************
public:	
	ACWeapon();
	EWeaponType GetType();
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
	EWeaponType Type;
protected:
	virtual void BeginPlay() override;

//  *********************
//      Equip 세팅
//  *********************
protected:
	UPROPERTY(EditAnywhere, Category="Data")
		class UCWeaponAsset* WeaponData;

protected:
	bool bEquipped;
public:
	UFUNCTION(Category="Equip")
		void Equip();
	UFUNCTION(Category="Equip")
		virtual void EndEquip();
	UFUNCTION(Category="Equip")
		void UnEquip();
	UFUNCTION(Category="Equip")
		void EndUnEquip();


protected:
	class ACCharacter_Base* Owner;
	class UCStatusComponent* Status;
	class UCStateComponent* State;

};
