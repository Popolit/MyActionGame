/*
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructure.h"
#include "CEquipment.generated.h"

class ACCharacter_Base;
class UCStateComponent;
class UCStatusComponent;

DECLARE_MULTICAST_DELEGATE(FEquipmentBehavior);

//Equip, UnEquip 행동을 정의한 클래스
UCLASS(Blueprintable)
class CPORTFOLIO_API UCEquipment : public UObject
{
	GENERATED_BODY()
	
public:
	void BeginPlay(ACCharacter_Base* InOwner, const FEquipData& InEquipData, const FUnEquipData& InUnEquipData);


// Equip 상태 Check
public:
	FORCEINLINE const bool* GetEquipping() const { return &bEquipping; }
	FORCEINLINE const bool* GetBeginEquip() const { return &bBeginEquip; }
	FORCEINLINE const bool* GetBeginUnEquip() const { return &bBeginUnEquip; }

private:
	bool bEquipping;
	bool bBeginEquip;
	bool bBeginUnEquip;


// Equip & UnEquip
public:
	void Equip();
	void EndEquip();
	void UnEquip();
	void EndUnEquip();

public:
	FEquipmentBehavior OnEndEquip;
	FEquipmentBehavior OnEndUnEquip;

protected:
	UPROPERTY(BlueprintReadOnly)
	ACCharacter_Base* OwnerCharacter;

protected:
	UPROPERTY(BlueprintReadOnly)
		FEquipData EquipData;
	UPROPERTY(BlueprintReadOnly)
		FUnEquipData UnEquipData;

private:
	UCStateComponent* State;
	UCStatusComponent* Status;
};
*/
