#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructure.h"
#include "CEquipment.generated.h"

DECLARE_MULTICAST_DELEGATE(FEquipmentBehavior);

//Equip, UnEquip 행동을 정의한 클래스
UCLASS(Blueprintable)
class CPORTFOLIO_API UCEquipment : public UObject
{
	GENERATED_BODY()
	
public:
	void BeginPlay(class ACCharacter_Base* InOwner, const FEquipData& InEquipData, const FUnEquipData& InUnEquipData);

//  *********************
//      Equip bool
//  *********************
public:
	FORCEINLINE const bool* GetEquipping() { return &bEquipping; }
	FORCEINLINE bool GetBeginEquip() { return bBeginEquip; }
	FORCEINLINE bool GetBeginUnEquip() { return bBeginUnEquip; }

private:
	bool bEquipping;
	bool bBeginEquip;
	bool bBeginUnEquip;


//  *********************
//     Equip, Unequip
//  *********************
public:
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void EndEquip();
	void EndEquip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void UnEquip();
	void UnEquip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void EndUnEquip();
	void EndUnEquip_Implementation();

public:
	FEquipmentBehavior OnEndEquip;
	FEquipmentBehavior OnEndUnEquip;



//  *********************
//      데이터
//  *********************
protected:
	UPROPERTY(BlueprintReadOnly)
		class ACCharacter_Base* OwnerCharacter;

protected:
	UPROPERTY(BlueprintReadOnly)
		FEquipData EquipData;
	UPROPERTY(BlueprintReadOnly)
		FUnEquipData UnEquipData;

private:
	class UCStateComponent* State;
	class UCStatusComponent* Status;
};
