#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_EndEquip.generated.h"


UCLASS()
class CPORTFOLIO_API UCAN_EndEquip : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UCAN_EndEquip();
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	FString const NotifyName;
};
