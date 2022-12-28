#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.h"
#include "CActionCombo.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCActionCombo : public UCAction
{
	GENERATED_BODY()

public:
	UCActionCombo();
virtual void BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages) override;	
	
public:
	virtual void Pressed_Implementation() override;
	virtual void EndAction_Implementation() override;

public:
	virtual void BeginCombo();
	void SetComboEnable(bool IsComboEnable);

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		uint8 ComboIndex;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		uint8 ComboMax;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		uint8 DelayedIndex;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		uint8 DelayedComboMax;
	UPROPERTY(BlueprintReadOnly)
		bool bComboEnable;
	UPROPERTY(BlueprintReadOnly)
		bool bInputExist;
};
