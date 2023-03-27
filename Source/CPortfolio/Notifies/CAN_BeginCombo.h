#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_BeginCombo.generated.h"

DECLARE_DELEGATE(FOnBeginCombo)

UCLASS()
class CPORTFOLIO_API UCAN_BeginCombo : public UAnimNotify
{
	GENERATED_BODY()
	
	friend class UCAction_Combo;
	friend class UCAction_Combo_Branch;
public:
	UCAN_BeginCombo();
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	FOnBeginCombo OnBeginCombo;
	const FString NotifyName;
};
