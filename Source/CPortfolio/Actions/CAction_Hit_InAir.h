#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Base.h"
#include "Interfaces/CI_EventHandler.h"
#include "CAction_Hit_InAir.generated.h"

class UCStateComponent;
class UCStatusComponent;

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Hit_InAir : public UCAction_Base, public ICI_EventHandler
{
	GENERATED_BODY()
public:
	UCAction_Hit_InAir();
	
public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;

public:
	virtual void HandleEvent() override;

private:
	const FName EventName; 
	UCStateComponent* StateComponent;
	UCStatusComponent* StatusComponent;
};


