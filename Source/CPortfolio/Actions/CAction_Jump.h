#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.h"
#include "CAction_Jump.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Jump : public UCAction
{
	GENERATED_BODY()
public:
	virtual void Pressed_Implementation() override;
	virtual void Released_Implementation() override;
};
