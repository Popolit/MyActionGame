#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction_Evade.h"
#include "CAction_Evade_Aerial.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Evade_Aerial : public UCAction_Evade
{
	GENERATED_BODY()
public:
	virtual void Pressed_Implementation() override;
	virtual void EndAction_Implementation() override;
};
