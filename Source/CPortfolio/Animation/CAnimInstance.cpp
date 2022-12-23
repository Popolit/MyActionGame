#include "Animation/CAnimInstance.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CFeetComponent.h"
#include "Components/CWeaponComponent.h"
#include "CAnimMetaData.h"
#include "Components/CStateComponent.h"

#include "GameFramework/Character.h"
#include "Weapons/CEquipment.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	WeaponType = EWeaponType::Max;
	Owner = Cast<ACCharacter_Base>(TryGetPawnOwner());
	CheckNull(Owner);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(Owner);
	CheckNull(Weapon)
	Weapon->OnWeaponTypeChanged.AddUObject(this, &UCAnimInstance::OnWeaponTypeChanged);

	State = CHelpers::GetComponent<UCStateComponent>(Owner);
	CheckNull(State)
	State->OnStateTypeChanged.AddDynamic(this, &UCAnimInstance::OnStateTypeChanged);
	State->OnAerialConditionChanged.AddDynamic(this, &UCAnimInstance::OnAerialConditionChanged);
	
	Feet = CHelpers::GetComponent<UCFeetComponent>(Owner);
	bFeetIK = false;

	CheckNull(Feet);
	bFeetIK = true;

	
	OnMontageEnded.AddDynamic(this, &UCAnimInstance::OnAnimMontageEnded);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Owner);
	
	bIsInAir = State->IsInAir();
	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());

	if(bFeetIK)
		FeetData = Feet->GetData();
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType PrevWeaponType, EWeaponType NewWeaponType)
{
	WeaponType = NewWeaponType;
}

void UCAnimInstance::OnStateTypeChanged(EStateType NewStateType)
{
	StateType = NewStateType;
}


void UCAnimInstance::OnAerialConditionChanged(bool IsInAir)
{
	bIsInAir = IsInAir;
}

void UCAnimInstance::OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if(!bInterrupted)
		return;
	//Equip 애니메이션 interrupt 시 equip 마무리
	
	if(!(Weapon->GetEquipment() == nullptr) && Weapon->GetEquipment()->GetBeginEquip())
	{
		Weapon->GetEquipment()->EndEquip();
		return;
	}
	CheckNull(Weapon->GetPrevEquipment());
	if(Weapon->GetPrevEquipment()->GetBeginUnEquip())
	{
		Weapon->GetPrevEquipment()->EndUnEquip();
		return;
	}
}
