#include "Weapon.h"

#include "WeaponAttachment.h"
#include "GameFramework/Character.h"

//Weapon 장비 시작
void UWeapon::Equip() const
{
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

//Weapon 장비 해제 시작
void UWeapon::UnEquip() const
{
	OwnerCharacter->PlayAnimMontage(UnEquipMontage);
}

//Weapon 장비 완료
void UWeapon::EndEquip() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		Attachment->EndEquip();
	}

	OwnerCharacter->bUseControllerRotationYaw = bUseControlRotation;

}

//Weapon 장비 해제 완료
void UWeapon::EndUnEquip() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		Attachment->EndUnEquip();
	}
}

//Attachment의 콜리전을 켬
void UWeapon::OnCollision() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		if(Attachment == nullptr)
		{
			continue;
		}
		Attachment->OnCollision();
	}
}

//Attachment의 콜리전을 끔
void UWeapon::OffCollision() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		if(Attachment == nullptr)
		{
			continue;
		}
		Attachment->OffCollision();
	}
}



void UWeapon::EndPlay(AActor* InOwner)
{
	for (AWeaponAttachment* Attachment : Attachments)
	{
		Attachment->Destroy();
		Attachment = nullptr;
	}
}
