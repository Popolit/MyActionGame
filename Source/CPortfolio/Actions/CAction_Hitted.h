#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.h"
#include "CAction_Hitted.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Hitted : public UCAction
{
	GENERATED_BODY()
public:
	virtual void Pressed_Implementation() override;
	virtual void EndAction_Implementation() override;
};
