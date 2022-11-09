#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CEquipData.generated.h"

UENUM()
enum class EquipType : uint8
{
	Equip, Unequip
};

USTRUCT(BlueprintType)
struct CPORTFOLIO_API FCEquipData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCEquipData();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EquipData")
    	EquipType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EquipData")
    	class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EquipData")
    	float Playratio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EquipData")
    	bool bUseControlRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EquipData")
    	bool bCanMove;

};
