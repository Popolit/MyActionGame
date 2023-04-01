#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Struct/FeetData.h"
#include "CAnimInstance.generated.h"

class ACCharacter_Base;
class UCWeaponComponent;
class UCFeetComponent;

UCLASS()
class CPORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    
private:
    UFUNCTION()
        void OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        bool bFeetIK;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        FFeetData FeetData;

private:
    ACCharacter_Base* OwnerCharacter;
    UCFeetComponent* FeetComponent;
};
