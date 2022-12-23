#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapons/Actions/CActionStructure.h"
#include "Weapons/CWeaponStructure.h"
#include "Struct/FeetData.h"
#include "CAnimInstance.generated.h"

UCLASS()
class CPORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

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
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
         EWeaponType WeaponType;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        bool bFeetIK;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        FFeetData FeetData;


public:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    UFUNCTION()
        void OnWeaponTypeChanged(EWeaponType PrevWeapon, EWeaponType NewWeapon);
    UFUNCTION()
        void OnStateTypeChanged(EStateType NewStateType);
    UFUNCTION()
        void OnAerialConditionChanged(bool IsInAir);
    UFUNCTION()
        void OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted);
    
private:
    class ACCharacter_Base* Owner;
    class UCWeaponComponent* Weapon;
    class UCStateComponent* State;
    class UCFeetComponent* Feet;
};
