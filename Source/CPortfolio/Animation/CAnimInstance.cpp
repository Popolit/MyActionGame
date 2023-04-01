#include "Animation/CAnimInstance.h"
#include "CHelpers.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CFeetComponent.h"
#include "Weapon.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacter_Base>(TryGetPawnOwner());
	if(OwnerCharacter == nullptr)
	{
		return;
	}
	
	FeetComponent = CHelpers::GetComponent<UCFeetComponent>(OwnerCharacter);
	bFeetIK = false;

	if(FeetComponent == nullptr)
	{
		return;
	}
	bFeetIK = true;

	
	OnMontageEnded.AddDynamic(this, &UCAnimInstance::OnAnimMontageEnded);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(OwnerCharacter == nullptr)
	{
		return;
	}
	if(bFeetIK)
	{
		FeetData = FeetComponent->GetData();
	}
}


void UCAnimInstance::OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if(!bInterrupted)
		return;
	//Equip 애니메이션 interrupt 시 equip 마무리
	/*if(Weapon->GetEquipment() != nullptr && Weapon->GetEquipment()->GetBeginEquip())
	{
		Weapon->GetEquipment()->EndEquip();
		return;
	}
	CheckNull(Weapon->GetPrevEquipment());
	if(Weapon->GetPrevEquipment()->GetBeginUnEquip())
	{
		Weapon->GetPrevEquipment()->EndUnEquip();
		return;
	}*/
}
