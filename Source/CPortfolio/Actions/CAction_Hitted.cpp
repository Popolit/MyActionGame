/*
#include "CAction_Hitted.h"
*/

/*
#include "Animation/CAnimInstance.h"
#include "Characters/CCharacter_Base.h"

void UCAction_Hitted::BeginPlay(ACCharacter_Base* InOwner, TArray<FActionData> const& InActionMontages)
{
	Super::BeginPlay(InOwner, InActionMontages);
	UCAnimInstance* animInstance = Cast<UCAnimInstance>(OwnerCharacter->GetMesh()->GetAnimInstance());
	OnHitted.BindUObject(animInstance, &UCAnimInstance::OnHitted);
}

void UCAction_Hitted::Pressed_Implementation()
{
	Super::Pressed_Implementation();
	
	Status->Stop();
	Status->StopAction();
	bStaggering = true;
	if(ActionMontages.Num() == 0)
		return;

	int32 const hitIndex = FMath::RandRange(0, ActionMontages.Num() - 1);
	ActionMontages[hitIndex].DoAction(OwnerCharacter);

	if(OnHitted.IsBound())
		OnHitted.Execute((uint8)hitIndex);
}

void UCAction_Hitted::EndAction_Implementation()
{
	Super::EndAction_Implementation();

	if(State->IsInAir())
		return;
	bStaggering = false;
	State->SetIdleMode();
	Status->Move();
	Status->Action();
}

void UCAction_Hitted::Tick(float const& InDeltaTime)
{
	if(StaggerTimeLeft < 0.f)
	{
		if(bStaggering)
			EndAction_Implementation();
		return;
	}
	
	StaggerTimeLeft -= InDeltaTime;
}

void UCAction_Hitted::SetTickTime(float const& InTime)
{
	StaggerTimeLeft = InTime;
}
*/
