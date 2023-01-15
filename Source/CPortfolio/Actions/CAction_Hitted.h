#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.h"
#include "CI_Action_Tick.h"
#include "CAction_Hitted.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Hitted : public UCAction, public ICI_Action_Tick
{
	GENERATED_BODY()
public:
	virtual void Pressed_Implementation() override;
	virtual void EndAction_Implementation() override;

public:
	virtual void Tick(float const& InDeltaTime) override;
	virtual void SetTickTime(float const& InTime) override;

private:
	float StaggerTimeLeft = 0.f;
	bool bStaggering = false;
};
