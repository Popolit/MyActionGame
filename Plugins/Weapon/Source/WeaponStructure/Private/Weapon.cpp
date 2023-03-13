#include "Weapon.h"

#include "WeaponAttachment.h"

void UWeapon::Equip()
{
	//ActionData->Equip();
}

void UWeapon::UnEquip()
{
	//ActionData->UnEquip();
}

void UWeapon::EndEquip()
{
}

void UWeapon::EndUnEquip()
{
}

void UWeapon::OnCollision()
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

void UWeapon::OffCollision()
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
	//ActionData->EndPlay();
}
