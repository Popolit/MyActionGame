#include "CAction_HasReplacement.h"
#include "CHelpers.h"

#include "CAction_Replacement.h"
#include "Components/CActionComponent.h"


UCAction_HasReplacement::UCAction_HasReplacement() : UCAction_Base(), SubjectAction(this)
{
}

void UCAction_HasReplacement::BeginPlay()
{
	Super::BeginPlay();
		
	for(TTuple<FName, TSubclassOf<UCAction_Replacement>> ClassOfActionToReplace : ClassOfActionsToReplace)
	{
		UCAction_Replacement* NewAction = NewObject<UCAction_Replacement>(this, ClassOfActionToReplace.Value.Get());
		NewAction->UAction::BeginPlay(OwnerCharacter);

		CHelpers::GetComponent<UCActionComponent>(OwnerCharacter)->BindActionEvent(ClassOfActionToReplace.Key, NewAction);
		NewAction->BindDelegations(this, &UCAction_HasReplacement::ReplaceAction, &UCAction_HasReplacement::RevertAction);
		ActionsToReplace.Push(NewAction);
	}
}

void UCAction_HasReplacement::KeyPressed()
{
	if(SubjectAction != this)
	{
		Cast<IIKeyInput>(SubjectAction)->KeyPressed();
	}
	else
	{
		HandleKeyPressed();
	}
}

void UCAction_HasReplacement::KeyReleased()
{
	if(SubjectAction != this)
	{
		Cast<IIKeyInput>(SubjectAction)->KeyReleased();
	}
	else
	{
		HandleKeyReleased();
	}
}


void UCAction_HasReplacement::ReplaceAction(UCAction_Base* InAction)
{
	SubjectAction = InAction;
}

void UCAction_HasReplacement::RevertAction()
{
	SubjectAction = this;
}


