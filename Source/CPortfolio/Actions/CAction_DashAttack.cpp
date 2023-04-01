#include "CAction_DashAttack.h"
#include "CHelpers.h"

#include "ActionFunctions.h"
#include "Components/CStateComponent.h"

void UCAction_DashAttack::BeginPlay()
{
	Super::BeginPlay();

	check(OwnerCharacter);
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);
}

void UCAction_DashAttack::BeginAction()
{
	Super::BeginAction();

	ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
	StateComponent->SetActionMode();
}

void UCAction_DashAttack::EndAction()
{
	Super::EndAction();
	ActionFunctions::EndAction(OwnerCharacter);
	StateComponent->SetIdleMode();
}

void UCAction_DashAttack::KeyPressed()
{
	Super::KeyPressed();

	if(ActionDatas.IsValidIndex(0))
	{
		BeginAction();
	}
}

void UCAction_DashAttack::OnCollision(AActor* InAttackCauser, AActor* InTargetActor)
{
	if(HitDatas.IsValidIndex(0))
	{
		ActionFunctions::PlayHitEffect(HitDatas[0], OwnerCharacter, InTargetActor);
		ActionFunctions::SendDamage(&HitDatas[0], OwnerCharacter, InAttackCauser, InTargetActor);
	}
}
