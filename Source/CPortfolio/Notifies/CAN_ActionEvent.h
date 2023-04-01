﻿#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Interfaces/CI_EventListener.h"
#include "CAN_ActionEvent.generated.h"

UCLASS()
class CPORTFOLIO_API UCAN_ActionEvent : public UAnimNotify, public ICI_EventListener
{
	GENERATED_BODY()
	
public:
	UCAN_ActionEvent();
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditInstanceOnly)
		FName EventName;
	
private:
	FOnEventTrigger OnEventTrigger;
	const FString NotifyName;
};
