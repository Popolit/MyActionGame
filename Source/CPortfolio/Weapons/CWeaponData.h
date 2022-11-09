#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructure.h"
#include "CWeaponData.generated.h"

UCLASS()
class CPORTFOLIO_API UCWeaponData : public UObject
{
	GENERATED_BODY()

private:
	friend class UCWeaponAsset;

public:
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UCEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UCAttack* GetAttack() { return Attack; }
	FORCEINLINE class UCSubAction* GetSubAction() { return SubAction; }

public:
	void EndPlay(ACharacter* InOwner);

private:
	UPROPERTY()
		class ACAttachment* Attachment;

	UPROPERTY()
		class UCEquipment* Equipment;

	UPROPERTY()
		FEquipData EquipmentData;

	UPROPERTY()
		class UCSubAction* SubAction;

	UPROPERTY()
		class UCAttack* Attack;

	UPROPERTY()
		TArray<FAttackData> AttackDatas;

	UPROPERTY()
		TArray<FHitData> HitDatas;
};
