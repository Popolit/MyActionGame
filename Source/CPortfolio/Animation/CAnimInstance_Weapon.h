#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CoreEnums.h"
#include "CAnimInstance_Weapon.generated.h"

class ACCharacter_Base;
class UCWeaponComponent;
class UCStateComponent;
class UCFeetComponent;

UCLASS()
class CPORTFOLIO_API UCAnimInstance_Weapon : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType NewStateType);
	
	UFUNCTION()
		void OnAerialConditionChanged(bool IsInAir);

public:
	UFUNCTION()
		void OnHit(uint8 InMontageIndex);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float AimPitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float AimYaw;
		
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		EStateType StateType;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
		uint8 HitMontageNum;
    
private:
	ACCharacter_Base* OwnerCharacter;
	UCStateComponent* StateComponent;
};
