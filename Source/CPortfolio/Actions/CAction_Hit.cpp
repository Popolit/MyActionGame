#include "CAction_Hit.h"
#include "CHelpers.h"

#include "ActionFunctions.h"
#include "CAction_Hit_InAir.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

#include "Kismet/KismetMathLibrary.h"

UCAction_Hit::UCAction_Hit() : UCAction_Base(), EventName("Hit"), StaggerTime(0.0f)
{
}

void UCAction_Hit::BeginPlay()
{
	Super::BeginPlay();

	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);
	
	StatusComponent = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	check(StatusComponent);
	
	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	check(ActionComponent);

	ActionComponent->BindActionEvent(EventName, this);
	StatusComponent->OnDamaged.AddUObject(this, &UCAction_Hit::OnDamaged);

	check(Action_Hit_InAirClass);
	Action_Hit_InAir = NewObject<UCAction_Hit_InAir>(this, Action_Hit_InAirClass);

	check(Action_Hit_InAir);
	Action_Hit_InAir->UAction::BeginPlay(OwnerCharacter);
}
void UCAction_Hit::BeginAction()
{
	Super::BeginAction();

	MontageIndex = UKismetMathLibrary::RandomIntegerInRange(0, ActionDatas.Num() - 1);
	if(ActionDatas.IsValidIndex(MontageIndex))
	{
		ActionFunctions::DoAction(ActionDatas[MontageIndex], OwnerCharacter);
	}
	StateComponent->SetHitMode();
	StatusComponent->DisableAction();
}

void UCAction_Hit::EndAction()
{
	Super::EndAction();
	if(ActionDatas.IsValidIndex(MontageIndex))
	{
		OwnerCharacter->PlayAnimMontage(ActionDatas[MontageIndex].Montage, ActionDatas[MontageIndex].PlayRatio, "Hit_LoopEnd");
	}
	StateComponent->SetIdleMode();
	StatusComponent->EnableMove();
	StatusComponent->EnableAction();
}

void UCAction_Hit::HandleEvent(bool IsEventOn)
{

}

void UCAction_Hit::Tick(float DeltaTime)
{
	if(0 < StaggerTime)
	{
		StaggerTime -= DeltaTime;
	}
	else if(!bActionEnded)
	{
		EndAction();
	}
}

TStatId UCAction_Hit::GetStatId() const
{
	return TStatId();
}

UWorld* UCAction_Hit::GetWorld() const
{
	return GetOuter()->GetWorld();
}


void UCAction_Hit::OnDamaged(float const& InAmount, float const& InStaggerTime)
{
	if(StateComponent->IsInAir())
	{
		Action_Hit_InAir->BeginAction();
		return;
	}
	
	if(!StateComponent->IsInAir() && 0 < InStaggerTime)
	{
		StaggerTime = InStaggerTime;
	}
	BeginAction();
}


