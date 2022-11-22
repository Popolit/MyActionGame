#include "Animation/CAnimInstance.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CFeetComponent.h"
#include "Components/CWeaponComponent.h"

#include "GameFramework/Character.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	WeaponType = EWeaponType::Max;
	Owner = Cast<ACCharacter_Base>(TryGetPawnOwner());
	CheckNull(Owner);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(Owner);
	CheckNull(Weapon)
	Weapon->OnWeaponChanged.AddUObject(this, &UCAnimInstance::OnWeaponTypeChanged);

	Feet = CHelpers::GetComponent<UCFeetComponent>(Owner);
	bFeetIK = false;

	CheckNull(Feet);
	bFeetIK = true;
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Owner);

	IsInAir = Owner->GetIsInAir();
	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());

	if(bFeetIK)
		FeetData = Feet->GetData();
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType NewWeaponType)
{
	WeaponType = NewWeaponType;
}
