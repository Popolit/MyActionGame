#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_EndAction.generated.h"

DECLARE_DELEGATE(FOnEndAction)

UCLASS()
class CPORTFOLIO_API UCAN_EndAction : public UAnimNotify
{
	GENERATED_BODY()
	friend class UCAction_Base;
	
public:
	UCAN_EndAction();
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
private:
	FString const NotifyName;
	FOnEndAction OnEndAction;
};
