#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CoreEnums.h"
#include "CSubAnimInstance.generated.h"

class ACCharacter_Base;
class UCWeaponComponent;
class UCStateComponent;
class UCFeetComponent;

UCLASS()
class CPORTFOLIO_API UCSubAnimInstance : public UAnimInstance
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
		EStateType StateType;
    
protected:
	ACCharacter_Base* OwnerCharacter;
	UCStateComponent* StateComponent;
};
