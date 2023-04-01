#pragma once

#include "CoreMinimal.h"
#include "CAction_Combo.h"
#include "Interfaces/CI_EventHandler.h"
#include "CAction_Combo_InAir.generated.h"


//공중 콤보 공격, 기존 공격과 달리 점프 당 1회만 액션 가능
UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Combo_InAir : public UCAction_Combo, public ICI_EventHandler
{
	GENERATED_BODY()
public:
	UCAction_Combo_InAir();

public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void HandleKeyPressed() override;

public:
	virtual void BeginCombo() override;
	virtual void HandleEvent() override;

private:
	UPROPERTY(EditDefaultsOnly)
		float LaunchZ;	//Launch Owner Character, Not TargetActor

private:
	bool bCanAction;
};


