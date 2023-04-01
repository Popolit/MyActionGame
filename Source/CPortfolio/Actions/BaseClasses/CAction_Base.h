#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "CAction_Base.generated.h"

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Base : public UAction
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

protected:
	void SetDirectionToCamera() const;
};
