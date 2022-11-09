#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructure.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentBehavior);

//Equip, Unequip 행동을 정의한 클래스
UCLASS(Blueprintable)
class CPORTFOLIO_API UCEquipment : public UObject
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACharacter* InOwner, const FEquipData& InEquipData, const FUnequipData& InUnequipData);

//  *********************
//      Equip bool
//  *********************
public:
	FORCEINLINE const bool* GetEquipping() { return &bEquipping; }
	FORCEINLINE bool GetBeginEquip() { return bBeginEquip; }

private:
	bool bEquipping;
	bool bBeginEquip;


//  *********************
//     Equip, Unequip
//  *********************
public:
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

public:
	UPROPERTY(BlueprintAssignable)
		FEquipmentBehavior OnEquip;

	UPROPERTY(BlueprintAssignable)
		FEquipmentBehavior OnUnequip;



//  *********************
//      데이터
//  *********************
protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

protected:
	UPROPERTY(BlueprintReadOnly)
		FEquipData EquipData;
	UPROPERTY(BlueprintReadOnly)
		FUnequipData UnequipData;

private:
	class UCStateComponent* State;
	class UCStatusComponent* Status;

};
