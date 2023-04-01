#pragma once

#include "CoreMinimal.h"
#include "Interfaces/CI_EventListener.h"
#include "CAN_RevertAction.generated.h"

class UCAction_Replacement;

UCLASS()
class CPORTFOLIO_API UCAN_RevertAction : public UAnimNotify, public ICI_EventListener
{
	GENERATED_BODY()
	
	UCAN_RevertAction();
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:
	UPROPERTY(EditInstanceOnly)
		FName EventName;
	
private:
	const FString NotifyName;
	FOnToggleEventTrigger OnToggleEventTrigger;
};
