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

	//캐릭터 세팅
	OwnerCharacter = Cast<ACCharacter_Base>(TryGetPawnOwner());
	if(OwnerCharacter == nullptr)
	{
		return;
	}

	//FeetIK 세팅
	FeetComponent = CHelpers::GetComponent<UCFeetComponent>(OwnerCharacter);
	bFeetIK = false;

	//FeetComponent를 가진 캐릭터는 FeetIK 사용 -> (차후 인터페이스 분리 염두)
	if(FeetComponent != nullptr)
	{
		bFeetIK = true;
	}

	//WeaponComponent 세팅
	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	//FABRIK 사용 무기 델리게이션
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
