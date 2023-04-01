#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CANS_MakeFlyingMode.generated.h"


UCLASS()
class CPORTFOLIO_API UCANS_MakeFlyingMode : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UCANS_MakeFlyingMode();
public:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	const FString NotifyName;
};
