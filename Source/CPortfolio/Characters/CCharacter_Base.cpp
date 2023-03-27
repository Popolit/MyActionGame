#include "Characters/CCharacter_Base.h"
#include "CHelpers.h"

#include "Components/CActionComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CFeetComponent.h"
#include "Weapon.h"

#include "GameFramework/CharacterMovementComponent.h"


ACCharacter_Base::ACCharacter_Base() : LaunchZ_InAir(FVector(0, 0, 250.f))
{
	//Weapon 설정
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "Weapon");
	CHelpers::CreateActorComponent<UCActionComponent>(this, &ActionComponent, "Action");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &StatusComponent, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "State");
	CHelpers::CreateActorComponent<UCFeetComponent>(this, &FeetComponent, "Feet");
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
	if(OnJumped.IsBound())
		OnJumped.Broadcast();
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
	/*if(DamageAmount == 0.f)
		return 0.f;
	if(!DamageEvent.IsOfType(FActionDamageEvent::ClassID))
		return 0.f;
	
	FActionDamageEvent* const ActionDamageEvent = (FActionDamageEvent*) &DamageEvent;

	//데미지 방향 벡터 설정
	FVector damageDirection;

	//직접 타격
	if(EventInstigator)
		damageDirection = GetActorLocation() - EventInstigator->GetPawn()->GetActorLocation();
	//스킬 등 투사체 타격
	else
		damageDirection = GetActorLocation() - DamageCauser->GetActorLocation();
	damageDirection.Z = 0.f;
	damageDirection.Normalize();
	
	//넉백 벡터 설정
	FVector knockBack = damageDirection;
	knockBack *= ActionDamageEvent->HitData->Launch;
	knockBack.Z += ActionDamageEvent->HitData->LaunchZ;

	if(StateComponent->IsInAir())
		LaunchCharacter(knockBack.Z == 0.f ? LaunchZ_InAir : knockBack, true, true);
	else if(knockBack.Z == 0.f)
		LaunchCharacter(knockBack, true, false);
	else
		LaunchCharacter(knockBack, true, true);
	
	//캐릭터 방향 세팅
	SetActorRotation(UKismetMathLibrary::MakeRotFromX(-damageDirection));


	//피격 처리
	/*ActionDamageEvent->HitData->PlayHitStop(GetWorld());
	ActionDamageEvent->HitData->PlayEffect(GetWorld(), GetActorLocation());
	ActionDamageEvent->HitData->PlaySoundCue(this);#1#
	
	StatusComponent->Damage(DamageAmount);
	StateComponent->SetHittedMode();
	
	/*
	UCAction_Base* action = ActionComponent->GetAction(EActionType::None);
	ICI_Tickable* tickableAction = Cast<ICI_Tickable>(action);

	if(tickableAction)
		tickableAction->SetTickTime(actionDamageEvent->HitData->StaggerTime);
		#1#

	return DamageAmount;*/
	return DamageAmount;
}







