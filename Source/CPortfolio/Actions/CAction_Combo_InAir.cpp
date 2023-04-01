#include "CAction_Combo_InAir.h"
#include "CHelpers.h"

#include "ActionFunctions.h"
#include "Components/CActionComponent.h"

UCAction_Combo_InAir::UCAction_Combo_InAir() :  LaunchZ(250.0f), bCanAction(false)
{
}

void UCAction_Combo_InAir::BeginPlay()
{
	Super::BeginPlay();

	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	check(ActionComponent);

	ActionComponent->BindActionEvent("Jump", this);
	ActionComponent->BindActionEvent("Airborne", this);
}

void UCAction_Combo_InAir::BeginAction()
{
	Super::BeginAction();
	OwnerCharacter->LaunchCharacter({0, 0, LaunchZ}, false, true);
}

void UCAction_Combo_InAir::EndAction()
{
	Super::EndAction();
	bCanAction = false;
}

void UCAction_Combo_InAir::HandleKeyPressed()
{
	if(!bCanAction)
	{
		return;
	}
	
	Super::HandleKeyPressed();
}

void UCAction_Combo_InAir::BeginCombo()
{
	if(!bCanAction)
	{
		return;
	}
	
	Super::BeginCombo();
	OwnerCharacter->LaunchCharacter({0, 0, LaunchZ}, false, true);
}

//점프가 일어나면 초기화
void UCAction_Combo_InAir::HandleEvent()
{
	bCanAction = true;
}

