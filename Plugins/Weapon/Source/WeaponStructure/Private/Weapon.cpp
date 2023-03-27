#include "Weapon.h"

#include "WeaponAttachment.h"
#include "GameFramework/Character.h"

void UWeapon::Equip() const
{
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void UWeapon::UnEquip() const
{
	OwnerCharacter->PlayAnimMontage(UnEquipMontage);
}

void UWeapon::EndEquip() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		Attachment->EndEquip();
	}
}

void UWeapon::EndUnEquip() const
{
	for(AWeaponAttachment* Attachment : Attachments)
	{
		Attachment->EndUnEquip();
	}
}

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
