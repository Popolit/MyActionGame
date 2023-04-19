#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Struct/FeetData.h"
#include "CAnimInstance.generated.h"

class ACCharacter_Base;
class AWeaponAttachment;
class UCFeetComponent;


/*
 * Default Character AnimInstance
 * Manage IK And AnimMontages
 */
UCLASS()
class CPORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
    void OnFABRIKWeapon(bool bFABRIKWeapon, AWeaponAttachment* Weapon);
    
private:
    UFUNCTION()
        void OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Character")
        bool bFeetIK;

    UPROPERTY(BlueprintReadOnly, Category = "Character")
        bool bFABRIK;
    
    UPROPERTY(BlueprintReadOnly, Category = "Character")
        FFeetData FeetData;

    UPROPERTY(BlueprintReadOnly, Category = "Character")
        FTransform FABRIKTransform;

private:
    ACCharacter_Base* OwnerCharacter;
    UCFeetComponent* FeetComponent;
    AWeaponAttachment* AttachmentHasFABRIK;
};


