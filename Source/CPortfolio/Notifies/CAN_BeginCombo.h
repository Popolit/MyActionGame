#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_BeginCombo.generated.h"


UCLASS()
class CPORTFOLIO_API UCAN_BeginCombo : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
