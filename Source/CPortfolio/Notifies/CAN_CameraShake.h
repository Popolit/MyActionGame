#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_CameraShake.generated.h"

UCLASS()
class CPORTFOLIO_API UCAN_CameraShake : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMatineeCameraShake> CameraShakeClass;

public:
	UCAN_CameraShake();

private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
