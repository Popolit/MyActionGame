#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_EndAction.generated.h"


UCLASS()
class CPORTFOLIO_API UCAN_EndAction : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UCAN_EndAction();
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

/*public:
	UPROPERTY(EditInstanceOnly)
		EActionType ActionType;*/
private:
	FString const NotifyName;
};
