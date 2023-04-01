#include "CAction_UpperAttack.h"
#include "CHelpers.h"

#include "ActionFunctions.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"

UCAction_UpperAttack::UCAction_UpperAttack() : bKeyPressed(false)
{
}

void UCAction_UpperAttack::BeginPlay()
{
	Super::BeginPlay();

	check(OwnerCharacter);
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);

	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	check(ActionComponent);

	ActionComponent->BindActionEvent("LongUpper", Cast<ICI_EventHandler>(this));
	
}

void UCAction_UpperAttack::BeginAction()
{
	Super::BeginAction();

	SetDirectionToCamera();
	OnActionReplacementTrigger.Execute(this);
	ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	StateComponent->SetActionMode();
}

void UCAction_UpperAttack::EndAction()
{
	Super::EndAction();
	ActionFunctions::EndAction(OwnerCharacter);
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	StateComponent->SetIdleMode();
}

void UCAction_UpperAttack::KeyPressed()
{
	Super::KeyPressed();

	bKeyPressed = true;
	if(ActionDatas.IsValidIndex(0))
	{
		BeginAction();
	}
}

void UCAction_UpperAttack::KeyReleased()
{
	Super::KeyReleased();
	bKeyPressed = false;
}

void UCAction_UpperAttack::HandleEvent()
{
	if(ActionDatas.IsValidIndex(1) && bKeyPressed)
	{
		ActionFunctions::DoAction(ActionDatas[1], OwnerCharacter);
	}
}

void UCAction_UpperAttack::OnCollision(AActor* InAttackCauser, AActor* InTargetActor)
{
	if(HitDatas.IsValidIndex(0))
	{
		ActionFunctions::PlayHitEffect(HitDatas[0], OwnerCharacter, InTargetActor);
		ActionFunctions::SendDamage(&HitDatas[0], OwnerCharacter, InAttackCauser, InTargetActor);
	}
}
