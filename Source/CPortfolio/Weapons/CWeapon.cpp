#include "CWeapon.h"
#include "Global.h"

#include "CWeaponAsset.h"

#include "Characters/CCharacter_Base.h"

ACWeapon::ACWeapon()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
}

EWeaponType ACWeapon::GetType()
{
	return Type;
}

void ACWeapon::BeginPlay()
{
	Owner = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(Owner);

	CheckNull(WeaponData);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), WeaponData->HolsterSocketName);
}


//  *********************
//      Equip Ã³¸®
//  *********************
void ACWeapon::Equip()
{
	FEquipData Data = WeaponData->EquipData;
	CheckNull(Data.Montage);
	Owner->PlayAnimMontage(Data.Montage, Data.PlayRatio);
}

void ACWeapon::EndEquip() 
{
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), WeaponData->RightHandSocketName);
}

void ACWeapon::UnEquip()
{
	FUnequipData Data = WeaponData->UnequipData;
	CheckNull(Data.Montage);
	Owner->PlayAnimMontage(Data.Montage, Data.PlayRatio);
}

void ACWeapon::EndUnEquip()
{
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), WeaponData->HolsterSocketName);
}
