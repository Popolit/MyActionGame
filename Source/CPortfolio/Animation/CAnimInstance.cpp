#include "Animation/CAnimInstance.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CWeaponComponent.h"

#include "GameFramework/Character.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	WeaponType = EWeaponType::Max;
	Owner = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(Owner);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(Owner);
	CheckNull(Weapon)
	Weapon->OnWeaponChanged.AddUObject(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Owner);

	IsInAir = Owner->GetIsInAir();
	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType NewWeaponType)
{
	WeaponType = NewWeaponType;
}
