#include "Weapon.h"

#include "WeaponAttachment.h"
#include "GameFramework/Character.h"

//Weapon ��� ����
void UWeapon::Equip() const
{
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

//Weapon ��� ���� ����
void UWeapon::UnEquip() const
{
	OwnerCharacter->PlayAnimMontage(UnEquipMontage);
}

//Weapon ��� �Ϸ�
void UWeapon::EndEquip() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		Attachment->EndEquip();
	}

	OwnerCharacter->bUseControllerRotationYaw = bUseControlRotation;

}

//Weapon ��� ���� �Ϸ�
void UWeapon::EndUnEquip() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		Attachment->EndUnEquip();
	}
}

//Attachment�� �ݸ����� ��
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

//Attachment�� �ݸ����� ��
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
