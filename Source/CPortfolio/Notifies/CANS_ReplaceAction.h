#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Interfaces/CI_EventListener.h"
#include "CANS_ReplaceAction.generated.h"

class UCAction_Replacement;

UCLASS()
class CPORTFOLIO_API UCANS_ReplaceAction : public UAnimNotifyState, public ICI_EventListener
{
	GENERATED_BODY()
	
	UCANS_ReplaceAction();
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditInstanceOnly)
		FName EventName;
	
private:
	const FString NotifyName;
	FOnToggleEventTrigger OnToggleEventTrigger;
};
