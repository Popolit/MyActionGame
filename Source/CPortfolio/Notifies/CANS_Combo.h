#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CANS_Combo.generated.h"

DECLARE_DELEGATE_OneParam(FOnEnableCombo, bool)

UCLASS()
class CPORTFOLIO_API UCANS_Combo : public UAnimNotifyState
{
	GENERATED_BODY()

	friend class UCAction_Combo;
	friend class UCAction_Combo_Branch;

	UCANS_Combo();
	
public:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	FOnEnableCombo OnEnableCombo;
	const FString NotifyName;
};
