#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAN_EndUnEquip.generated.h"


UCLASS()
class CPORTFOLIO_API UCAN_EndUnEquip : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	//UCAN_EndEquip();

	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
