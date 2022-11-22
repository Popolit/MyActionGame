#pragma once

#include "CoreMinimal.h"
#include "FeetData.generated.h"

//Feet IK 데이터
USTRUCT(BlueprintType)
struct CPORTFOLIO_API FFeetData
{
	GENERATED_USTRUCT_BODY()
public:
	FFeetData();
	FFeetData(FVector LeftDistance
		, FVector RightDistance
		, FVector PelvisDistance
		, FRotator LeftRotation
		, FRotator RightRotation);
public:
	UPROPERTY(BlueprintReadOnly, Category = "FeetIK")
		FVector LeftDistance;
	UPROPERTY(BlueprintReadOnly, Category = "FeetIK")
		FVector RightDistance;
	UPROPERTY(BlueprintReadOnly, Category = "FeetIK")
		FVector PelvisDistance;
	UPROPERTY(BlueprintReadOnly, Category = "FeetIK")
		FRotator LeftRotation;
	UPROPERTY(BlueprintReadOnly, Category = "FeetIK")
		FRotator RightRotation;
};
