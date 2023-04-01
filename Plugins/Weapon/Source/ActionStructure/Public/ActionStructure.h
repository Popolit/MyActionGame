#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine.h"
#include "ActionStructure.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Action, SubAction, Skill_A, Skill_B, Jump, Evade, None
};


/////////////////////////////////////////////////////////////////

class UFXSystemAsset;
class USoundCue;

USTRUCT(BlueprintType)
struct FHitData
{
	GENERATED_BODY()
public:
	FHitData();

public:
	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		float Launch;

	UPROPERTY(EditAnywhere)
		float LaunchZ;
	
	UPROPERTY(EditAnywhere)
		float StaggerTime;

	UPROPERTY(EditAnywhere)
		float StopTime;

	UPROPERTY(EditAnywhere)
		UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FVector EffectLocation;

	UPROPERTY(EditAnywhere)
		FVector EffectScale;

	UPROPERTY(EditAnywhere)
		USoundCue* SoundCue;
};


/////////////////////////////////////////////////////////////////


USTRUCT()
struct FActionDamageEvent : public FDamageEvent
{
	GENERATED_BODY()
public:
	FHitData* HitData;
};


/////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct ACTIONSTRUCTURE_API FActionTrigger
{
	GENERATED_BODY()
public:
	FActionTrigger();
	FActionTrigger(bool InIsInAir, EActionType InActionType);
	FActionTrigger(const FActionTrigger& Other);
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Trigger")
		bool IsInAir;
	UPROPERTY(EditDefaultsOnly, Category="Trigger")
		EActionType ActionType;
	
public:
	bool operator==(const FActionTrigger& Other) const
	{
		return IsInAir == Other.IsInAir &&
			ActionType == Other.ActionType;
	}
	friend uint32 GetTypeHash(const FActionTrigger& Other)
	{
		return FCrc::MemCrc32(&Other, sizeof(FActionTrigger));
	}
};

/////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FActionData
{
	GENERATED_BODY()
public:
	FActionData();
	
public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio;

	UPROPERTY(EditAnywhere)
		bool bCanMove;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera;
};