#include "Characters/CCharacter_Base.h"
#include "CHelpers.h"

#include "Weapon.h"
#include "Components/CActionComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CFeetComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


ACCharacter_Base::ACCharacter_Base() : LaunchZ_InAir(0, 0, 250)
{
	//Weapon ����
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "Weapon");
	CHelpers::CreateActorComponent<UCActionComponent>(this, &ActionComponent, "Action");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &StatusComponent, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "State");
	CHelpers::CreateActorComponent<UCFeetComponent>(this, &FeetComponent, "Feet");
}

void ACCharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	OnJumpEventTrigger.BindUObject(ActionComponent, &UCActionComponent::OnActionEvent);
}

bool ACCharacter_Base::IsInAir()
{
	return StateComponent->IsInAir();
}

void ACCharacter_Base::OnWeaponChanged(UWeapon* PrevWeapon, UWeapon* NewWeapon)
{
	check(NewWeapon);

	GetMesh()->SetAnimInstanceClass(NewWeapon->GetAnimClass());
}
void ACCharacter_Base::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PrevCustomMode);
	EMovementMode NewMovementMode = GetCharacterMovement()->MovementMode;
	if(NewMovementMode == EMovementMode::MOVE_Flying)
		StateComponent->SetIsInAir(true);
}

void ACCharacter_Base::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	StateComponent->SetIsInAir(true);
	if(OnJumpEventTrigger.IsBound())
	{
		OnJumpEventTrigger.Execute("Jump");
	}
}

void ACCharacter_Base::OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta)
{
	Super::OnWalkingOffLedge_Implementation(PreviousFloorImpactNormal, PreviousFloorContactNormal, PreviousLocation, TimeDelta);

	StateComponent->SetIsInAir(true);
}

void ACCharacter_Base::LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	Super::LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);
	if(!bZOverride)
		return;
	StateComponent->SetIsInAir(true);
}

void ACCharacter_Base::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	StateComponent->SetIsInAir(false);
}
float ACCharacter_Base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(!DamageEvent.IsOfType(FActionDamageEvent::ClassID))
		return 0.0f;
	
	FActionDamageEvent* const ActionDamageEvent = (FActionDamageEvent*) &DamageEvent;

	//������ ���� ���� ����
	FVector DamageDirection;

	//���� Ÿ��
	if(EventInstigator)
	{
		DamageDirection = GetActorLocation() - EventInstigator->GetPawn()->GetActorLocation();
	}
	//��ų �� ����ü Ÿ��
	else
	{
		DamageDirection = GetActorLocation() - DamageCauser->GetActorLocation();
	}
	DamageDirection.Z = 0.0f;
	DamageDirection.Normalize();
	
	//�˹� ���� ����
	FVector KnockBack = DamageDirection;
	KnockBack *= ActionDamageEvent->HitData->Launch;
	KnockBack.Z += ActionDamageEvent->HitData->LaunchZ;

	//����϶�, �⺻������ ü���ð��� �ø�. Z�� �˹��� 0�� �ƴ� ��� Ŀ���� �˹� ����
	if(StateComponent->IsInAir())
	{
		LaunchCharacter(KnockBack.Z == 0.0f ? LaunchZ_InAir : KnockBack, true, true);
	}
	//����, ��� ���� �ƴ�
	else if(KnockBack.Z == 0.f)
	{
		LaunchCharacter(KnockBack, true, false);
	}
	//����, ��� ���� �ǰ�
	else
	{
		LaunchCharacter(KnockBack, true, true);
	}
	
	//ĳ���� ���� ����
	SetActorRotation(UKismetMathLibrary::MakeRotFromX(-DamageDirection));
	
	StatusComponent->Damage(DamageAmount, ActionDamageEvent->HitData->StaggerTime);
	
	/*
	UCAction_Base* action = ActionComponent->GetAction(EActionType::None);
	ICI_Tickable* tickableAction = Cast<ICI_Tickable>(action);

	if(tickableAction)
		tickableAction->SetTickTime(actionDamageEvent->HitData->StaggerTime);
		#1#

	return DamageAmount;*/
	return DamageAmount;
}






