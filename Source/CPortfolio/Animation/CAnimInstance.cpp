#include "Animation/CAnimInstance.h"
#include "CHelpers.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CFeetComponent.h"
#include "Components/CWeaponComponent.h"
#include "WeaponAttachment.h"
#include "Interfaces/CI_WeaponHasFABRIK.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	//ĳ���� ����
	OwnerCharacter = Cast<ACCharacter_Base>(TryGetPawnOwner());
	if(OwnerCharacter == nullptr)
	{
		return;
	}

	//FeetIK ����
	FeetComponent = CHelpers::GetComponent<UCFeetComponent>(OwnerCharacter);
	bFeetIK = false;

	//FeetComponent�� ���� ĳ���ʹ� FeetIK ��� -> (���� �������̽� �и� ����)
	if(FeetComponent != nullptr)
	{
		bFeetIK = true;
	}

	//WeaponComponent ����
	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	//FABRIK ��� ���� �������̼�
	if(WeaponComponent != nullptr)
	{
		WeaponComponent->OnFABRIKWeapon.BindUObject(this, &UCAnimInstance::OnFABRIKWeapon);
	}
	
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
	if(bFABRIK)
	{
		FABRIKTransform = ICI_WeaponHasFABRIK::Execute_GetFABRIKTransform(AttachmentHasFABRIK);
	}
}

void UCAnimInstance::OnFABRIKWeapon(bool bFABRIKWeapon, AWeaponAttachment* Weapon)
{
	bFABRIK = bFABRIKWeapon;
	AttachmentHasFABRIK = Weapon;
}

void UCAnimInstance::OnAnimMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if(!bInterrupted)
		return;
	//Equip �ִϸ��̼� interrupt �� equip ������
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
