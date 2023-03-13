#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CoreEnums.h"
#include "Struct/FeetData.h"
#include "CAnimInstance.generated.h"

class ACCharacter_Base;
class UCWeaponComponent;
class UCStateComponent;
class UCFeetComponent;

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

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        uint8 HitMontageNum;


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

public:
    UFUNCTION()
        void OnHitted(uint8 InMontageIndex);
    
private:
    ACCharacter_Base* Owner;
    UCWeaponComponent* Weapon;
    UCStateComponent* State;
    UCFeetComponent* Feet;
};
