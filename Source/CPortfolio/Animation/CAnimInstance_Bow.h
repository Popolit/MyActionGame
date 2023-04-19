#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/CI_EventHandler.h"
#include "CAnimInstance_Bow.generated.h"

UCLASS()
class CPORTFOLIO_API UCAnimInstance_Bow : public UAnimInstance, public ICI_EventHandler
{
	GENERATED_BODY()
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	virtual void HandleEvent() override;
};
