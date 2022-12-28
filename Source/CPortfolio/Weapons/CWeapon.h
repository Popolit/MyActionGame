#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructure.h"
#include "CWeapon.generated.h"



UCLASS()
class CPORTFOLIO_API UCWeapon : public UObject
{
	GENERATED_BODY()

private:
	friend class UCWeaponAsset;
	
public:
	FORCEINLINE EWeaponType GetType() { return Type; }
	FORCEINLINE TArray<class ACAttachment*> const* GetAttachments() { return &Attachments; }
	FORCEINLINE class UCEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class UCActionData* GetActionData() { return ActionData; }

public:
	void EndPlay(class ACCharacter_Base* InOwner);
	
private:
	UPROPERTY()
		EWeaponType Type;
	
	UPROPERTY()
		TArray<class ACAttachment*> Attachments;

	UPROPERTY()
		class UCEquipment* Equipment;

	UPROPERTY()
		class UCActionData* ActionData;
};


