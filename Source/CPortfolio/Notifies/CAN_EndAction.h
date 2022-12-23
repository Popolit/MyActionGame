#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Weapons/Actions/CActionStructure.h"
#include "CAN_EndAction.generated.h"


UCLASS()
class CPORTFOLIO_API UCAN_EndAction : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditInstanceOnly)
		EActionType ActionType = EActionType::None;
};
