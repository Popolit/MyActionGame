#include "CWeapon.h"
#include "Global.h"

#include "CWeaponAsset.h"
#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"


//  *********************
//      기본 세팅
//  *********************
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

	Status = CHelpers::GetComponent<UCStatusComponent>(Owner);
	State = CHelpers::GetComponent<UCStateComponent>(Owner);
	
	CheckNull(WeaponData);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), WeaponData->HolsterSocketName);
}


//  *********************
//      Equip 처리
//  *********************
void ACWeapon::Equip()
{
	FEquipData Data = WeaponData->EquipData;
	CheckNull(Data.Montage);
	Owner->PlayAnimMontage(Data.Montage, Data.PlayRatio);

	if(!Data.bCanMove)
		Status->Stop();
	if(Data.bUseControlRotation)
		Status->EnableControlRotation();
}

void ACWeapon::EndEquip() 
{
	FEquipData Data = WeaponData->EquipData;
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), WeaponData->RightHandSocketName);
	Status->Move();
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
	Status->DisableControlRotation();
}
