#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWeaponStructure.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword, Shotgun, Max,
};

USTRUCT(BlueprintType)
struct FEquipData
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
		bool bUseControlRotation = true;
};

///////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FUnEquipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;
};
USTRUCT(BlueprintType)
struct FHitData
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
		float Power = 0;

	UPROPERTY(EditAnywhere)
		float Launch = 100;

	UPROPERTY(EditAnywhere)
		float StopTime = 0;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;

	UPROPERTY(EditAnywhere)
		class USoundCue* SoundCue;

public:
	void PlayMontage(class ACharacter* InOwner);
	void PlayHitStop(class UWorld* InWorld);
	void PlaySoundCue(class ACharacter* InOwner);
	void PlayEffect(class UWorld* InWorld, const FVector& InLocation);
	void SendDamage(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter);
};

USTRUCT(BlueprintType)
struct FActionDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	FHitData* HitData;
};

///////////////////////////////////////////////////////////////////////////////

USTRUCT(BlueprintType)
struct FActionContent
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

	UPROPERTY(EditAnywhere)
		FHitData HitData;

public:
	void DoAction(class ACCharacter_Base* InOwner);
	void EndAction(class ACCharacter_Base* InOwner);

	void PlayEffect(class ACCharacter_Base* InOwner);
	void PlayEffect(class USkeletalMeshComponent* InMesh, FName InSocketName = NAME_None);
};


///////////////////////////////////////////////////////////////////////////////

UCLASS()
class CPORTFOLIO_API UCWeaponStructure : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE static class UAnimMontage* GetDefault_HitMontage() { return Default_HitMontage; }

public:
	UCWeaponStructure();

private:
	static class UAnimMontage* Default_HitMontage;
};
