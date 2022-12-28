#include "CAction.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Weapons/CAttachment.h"
#include "Actions/CActionStructure.h"

UCAction::UCAction()
{
}

void UCAction::BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages)
{
	OwnerCharacter = InOwner;
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	ActionMontages = InActionMontages;
}

void UCAction::Pressed_Implementation()
{
}

void UCAction::Released_Implementation()
{
}

void UCAction::DoAction_Implementation(FActionMontage const& InActionMontage)
{
	InActionMontage.DoAction(OwnerCharacter);
}

void UCAction::EndAction_Implementation()
{
	if (!!Status)
	{
		Status->Move();
		Status->DisableFixedCamera();
	}
}

void UCAction::PlayEffect(FActionMontage const& InActionMontage)
{
	InActionMontage.PlayEffect(OwnerCharacter);
}

void UCAction::PlayEffectAtSocket(FActionMontage const& InActionMontage, USkeletalMeshComponent* InMesh, FName InSocketName)
{
	InActionMontage.PlayEffect(InMesh, InSocketName);
}