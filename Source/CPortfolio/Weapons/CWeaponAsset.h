#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponStructure.h"
#include "CWeaponAsset.generated.h"


UCLASS()
class CPORTFOLIO_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	friend class ACWeapon;

private:
	UPROPERTY(EditAnywhere, Category="Equip")
		FEquipData EquipData;

	UPROPERTY(EditAnywhere, Category="Equip")
		FUnequipData UnequipData;

	UPROPERTY(EditAnywhere, Category="Equip")
		FName HolsterSocketName;

	UPROPERTY(EditAnywhere, Category="Equip")
		FName RightHandSocketName;

	UPROPERTY(EditAnywhere, Category="Equip")
		FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category="Actions")
		TSubclassOf<class UCSubAction> SubActionClass;

	UPROPERTY(EditAnywhere, Category="Actions")
		TSubclassOf<class UCAttack> AttackClass;

	UPROPERTY(EditAnywhere, Category="Actions")
		TArray<FAttackData> AttackDatas;

	UPROPERTY(EditAnywhere)
		TArray<FHitData> HitDatas;

private:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutWeaponData);

public:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
};
