#include "CSubAnimInstance.h"
#include "CHelpers.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Weapon.h"

#include "GameFramework/Character.h"


void UCSubAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacter_Base>(TryGetPawnOwner());
	if(OwnerCharacter == nullptr)
	{
		return;
	}

	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	if(StateComponent == nullptr)
	{
		return;
	}
	
	StateComponent->OnStateTypeChanged.AddUObject(this, &UCSubAnimInstance::OnStateTypeChanged);
	StateComponent->OnAerialConditionChanged.AddUObject(this, &UCSubAnimInstance::OnAerialConditionChanged);
}

void UCSubAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(OwnerCharacter == nullptr)
	{
		return;
	}
	
	bIsInAir = StateComponent->IsInAir();
	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
	AimPitch = OwnerCharacter->GetBaseAimRotation().Pitch;
}


void UCSubAnimInstance::OnStateTypeChanged(EStateType NewStateType)
{
	StateType = NewStateType;
}

void UCSubAnimInstance::OnAerialConditionChanged(bool IsInAir)
{

	bIsInAir = IsInAir;
}

void UCSubAnimInstance::OnHit(uint8 InMontageIndex)
{
	HitMontageNum = InMontageIndex;
}
