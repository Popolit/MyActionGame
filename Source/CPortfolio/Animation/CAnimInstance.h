#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapons/CWeaponStructure.h"
#include "Struct/FeetData.h"
#include "CAnimInstance.generated.h"

UCLASS()
class CPORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        bool IsInAir;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        float Speed;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        float Direction;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        float AimPitch;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        float AimYaw;
    
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
        void OnWeaponTypeChanged(EWeaponType NewWeapon);
    
private:
    class ACCharacter_Base* Owner;
    class UCWeaponComponent* Weapon;
    class UCFeetComponent* Feet;
};
