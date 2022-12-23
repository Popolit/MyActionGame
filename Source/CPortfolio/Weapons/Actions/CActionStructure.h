#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/CStateComponent.h"
#include "CActionStructure.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Action, SubAction, Skill_A, Skill_B, Jump, Dash, None
};

/////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct CPORTFOLIO_API FActionTrigger
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Trigger")
		EStateType StateType;
	UPROPERTY(EditAnywhere, Category="Trigger")
		bool IsInAir;
	UPROPERTY(EditAnywhere, Category="Trigger")
		EActionType ActionType;
	
	FActionTrigger() : FActionTrigger(EStateType::Max, false, EActionType::None) {}
	FActionTrigger(EStateType InStateType, bool IsInAir, EActionType InActionType) : StateType(InStateType), IsInAir(IsInAir), ActionType(InActionType) {}
	FActionTrigger(const FActionTrigger& Other) : FActionTrigger(Other.StateType, Other.IsInAir, Other.ActionType) {}
	
	bool operator==(const FActionTrigger& Other) const
	{
		return StateType == Other.StateType &&
			IsInAir == Other.IsInAir &&
			ActionType == Other.ActionType;
	}
	friend uint32 GetTypeHash(const FActionTrigger& Other)
	{
		return FCrc::MemCrc32(&Other, sizeof(FActionTrigger));
	}
};
/////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FActionMontage
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere)
	bool bFixedCamera = false;
        
	UPROPERTY(EditAnywhere)
	class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
	FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FVector EffectScale = FVector::OneVector;

	/*UPROPERTY(EditAnywhere)
	FHitData HitData;*/

public:
	void DoAction(class ACCharacter_Base* InOwner) const;

	void PlayEffect(class ACCharacter_Base* InOwner) const;
	void PlayEffect(class USkeletalMeshComponent* InMesh, FName InSocketName = NAME_None) const;
};

/////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FActionData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCAction> ActionClass;
	
	UPROPERTY(EditAnywhere, Category="Trigger", meta=(Bitmask, BitmaskEnum = "EStateType"))
		uint32 StateTypeFlags;
	UPROPERTY(EditAnywhere, Category="Trigger")
		bool IsInAir;
	UPROPERTY(EditAnywhere, Category="Trigger")
		EActionType ActionType;
	
	UPROPERTY(EditAnywhere)
		TArray<FActionMontage> Montages;
};
