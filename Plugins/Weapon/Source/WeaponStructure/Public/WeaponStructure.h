#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "WeaponStructure.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FEquipData
{
	GENERATED_BODY()
public:
	FEquipData();
	
public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio;

	UPROPERTY(EditAnywhere)
		bool bCanMove;

	UPROPERTY(EditAnywhere)
		bool bUseControlRotation;
};

///////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FUnEquipData
{
	GENERATED_BODY()
public:
	FUnEquipData();

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio;
};
