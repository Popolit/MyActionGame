#include "CAnimInstance_Weapon.h"
#include "CHelpers.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Weapon.h"

#include "GameFramework/Character.h"


void UCAnimInstance_Weapon::NativeBeginPlay()
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
	
	StateComponent->OnStateTypeChanged.AddUObject(this, &UCAnimInstance_Weapon::OnStateTypeChanged);
	StateComponent->OnAerialConditionChanged.AddUObject(this, &UCAnimInstance_Weapon::OnAerialConditionChanged);
}

void UCAnimInstance_Weapon::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(OwnerCharacter == nullptr)
	{
		return;
	}
	
	bIsInAir = StateComponent->IsInAir();
	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
}


void UCAnimInstance_Weapon::OnStateTypeChanged(EStateType NewStateType)
{
	StateType = NewStateType;
}

void UCAnimInstance_Weapon::OnAerialConditionChanged(bool IsInAir)
{

	bIsInAir = IsInAir;
}

void UCAnimInstance_Weapon::OnHit(uint8 InMontageIndex)
{
	HitMontageNum = InMontageIndex;
}
