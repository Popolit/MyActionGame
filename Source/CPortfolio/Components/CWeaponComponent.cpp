#include "CWeaponComponent.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Weapons/CEquipment.h"
#include "Weapons/CWeaponAsset.h"
#include "Weapons/CWeapon.h"


//  *********************
//      �⺻ ����
//  *********************
UCWeaponComponent::UCWeaponComponent()
{
	CurrWeaponIndex = -1;
	PrevWeaponIndex = -1;
}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//���� ĳ���� ����
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter);

	//Weapon ����
	for(UCWeaponAsset* weapon : Weapons)
	{
		UCWeapon* newWeaponData;
		weapon->BeginPlay(OwnerCharacter, &newWeaponData);
		WeaponDatas.Emplace(newWeaponData);
	}

}


//  *********************
//      Weapon Asset
//  *********************

UCEquipment* UCWeaponComponent::GetEquipment()
{
	if(GetWeaponType(CurrWeaponIndex) == EWeaponType::Max)
		return NULL;
	return WeaponDatas[CurrWeaponIndex]->GetEquipment();
}

UCEquipment* UCWeaponComponent::GetPrevEquipment()
{
	if (GetWeaponType(PrevWeaponIndex) == EWeaponType::Max)
		return NULL;
	return WeaponDatas[PrevWeaponIndex]->GetEquipment();
}

EWeaponType UCWeaponComponent::GetWeaponType(int const& Index)
{
	if (Index == -1)
		return EWeaponType::Max;
	if (!WeaponDatas[CurrWeaponIndex])
		return EWeaponType::Max;

	return WeaponDatas[CurrWeaponIndex]->GetType();
}

UCActionData* UCWeaponComponent::GetActionData()
{
	if(!WeaponDatas.IsValidIndex(CurrWeaponIndex))
		return nullptr;
	return WeaponDatas[CurrWeaponIndex]->GetActionData();
}

//  *********************
//      Equip
//  *********************

void UCWeaponComponent::ChangeWeapon(int const& Index)
{
	if (WeaponDatas.Num() <= Index)
		return;

	PrevWeaponIndex = CurrWeaponIndex;
	//���� ���� �����̸� ����
	if (CurrWeaponIndex == Index)
		CurrWeaponIndex = -1;
	else
		CurrWeaponIndex = Index;

	UnEquipWeapon();
	EquipWeapon();

	if(OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(GetWeaponType(PrevWeaponIndex), GetWeaponType(CurrWeaponIndex));
}

void UCWeaponComponent::EquipWeapon()
{
	if (GetWeaponType(CurrWeaponIndex) == EWeaponType::Max)
		return;

	WeaponDatas[CurrWeaponIndex]->GetEquipment()->Equip();
}

void UCWeaponComponent::UnEquipWeapon()
{
	if (GetWeaponType(PrevWeaponIndex) == EWeaponType::Max)
		return;

	if(GetWeaponType(CurrWeaponIndex) == EWeaponType::Max)
		WeaponDatas[PrevWeaponIndex]->GetEquipment()->UnEquip();
	else
		WeaponDatas[PrevWeaponIndex]->GetEquipment()->EndUnEquip();
}

