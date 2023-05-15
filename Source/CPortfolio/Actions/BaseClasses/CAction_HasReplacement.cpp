#include "CAction_HasReplacement.h"
#include "CHelpers.h"

#include "CAction_Replacement.h"
#include "Components/CActionComponent.h"


UCAction_HasReplacement::UCAction_HasReplacement() : UCAction_Base(), SubjectAction(this)
{
}

/* BeginPlay - 모든 서브(교체될) 액션의 초기화 */
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

void UCAction_HasReplacement::EndAction()
{
	Super::EndAction();

	//만약 서브 액션이 끝난 상태라면 메인 액션으로 되돌림
	if(SubjectAction->IsActionEnded())
	{
		RevertAction();
	}
}

/**
 * KeyPressed - 서브 액션일 경우, 해당 액션의 KeyPressed를 실행
 * 만약, 메인 액션일 경우 HandleKeyPressed 함수로 처리
 */
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

/**
 * KeyReleased - 서브 액션일 경우, 해당 액션의 KeyReleased를 실행
 * 만약, 메인 액션일 경우 HandleKeyReleased 함수로 처리
 */
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

/**
 * 어떤 트리거로 인해 액션을 교체
 * @param InAction 교체될 액션
 */
void UCAction_HasReplacement::ReplaceAction(UCAction_Base* InAction)
{
	SubjectAction = InAction;
}

/* 대상 액션을 메인 액션으로 되돌림 */
void UCAction_HasReplacement::RevertAction()
{
	SubjectAction = this;
}


