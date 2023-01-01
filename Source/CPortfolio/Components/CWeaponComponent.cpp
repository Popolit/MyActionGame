#include "CWeaponComponent.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Weapons/CEquipment.h"
#include "Weapons/CWeaponAsset.h"
#include "Weapons/CWeapon.h"


//  *********************
//      기본 세팅
//  *********************
UCWeaponComponent::UCWeaponComponent()
{
	CHelpers::GetAsset(&UnarmedAsset, "/Game/Weapons/DA_Unarmed.DA_Unarmed");
	CurrWeaponIndex = 0;
	PrevWeaponIndex = 0;
}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//오너 캐릭터 세팅
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(OwnerCharacter);

	UCWeapon* newWeaponData;
	if(!!UnarmedAsset)
		UnarmedAsset->BeginPlay(OwnerCharacter, &newWeaponData);
	WeaponDatas.Push(newWeaponData);
	
	//Weapon 세팅
	for(UCWeaponAsset* weapon : Weapons)
	{
		weapon->BeginPlay(OwnerCharacter, &newWeaponData);
		WeaponDatas.Push(newWeaponData);
	}
}


//  *********************
//      Weapon Asset
//  *********************

UCEquipment* UCWeaponComponent::GetEquipment()
{
	if(!WeaponDatas.IsValidIndex(CurrWeaponIndex))
		return NULL;
	CheckNullResult(WeaponDatas[CurrWeaponIndex], NULL);
	return WeaponDatas[CurrWeaponIndex]->GetEquipment();
}

UCEquipment* UCWeaponComponent::GetPrevEquipment()
{
	if(!WeaponDatas.IsValidIndex(PrevWeaponIndex))
		return NULL;
	CheckNullResult(WeaponDatas[PrevWeaponIndex], NULL);
	return WeaponDatas[PrevWeaponIndex]->GetEquipment();
}

TArray<ACAttachment*> const* UCWeaponComponent::GetAttachments()
{
	if(!WeaponDatas.IsValidIndex(CurrWeaponIndex))
		return nullptr;
	CheckNullResult(WeaponDatas[CurrWeaponIndex], nullptr);
	return WeaponDatas[CurrWeaponIndex]->GetAttachments();
}

EWeaponType UCWeaponComponent::GetWeaponType(int const& Index)
{
	if(!WeaponDatas.IsValidIndex(CurrWeaponIndex))
		return EWeaponType::Max;
	CheckNullResult(WeaponDatas[CurrWeaponIndex], EWeaponType::Max);

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
	if (!WeaponDatas.IsValidIndex(Index))
		return;

	PrevWeaponIndex = CurrWeaponIndex;
	//장착 중인 무기이면 해제
	if (CurrWeaponIndex == Index)
		CurrWeaponIndex = 0;
	else
		CurrWeaponIndex = Index;

	UnEquipWeapon();
	EquipWeapon();

	if(OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(GetWeaponType(PrevWeaponIndex), GetWeaponType(CurrWeaponIndex));
}

void UCWeaponComponent::EquipWeapon()
{
	if(!WeaponDatas.IsValidIndex(CurrWeaponIndex))
		return;
	CheckNull(WeaponDatas[CurrWeaponIndex]);
	WeaponDatas[CurrWeaponIndex]->GetEquipment()->Equip();
}

void UCWeaponComponent::UnEquipWeapon()
{
	if(!WeaponDatas.IsValidIndex(CurrWeaponIndex))
		return;
	CheckNull(WeaponDatas[CurrWeaponIndex]);

	if(GetWeaponType(CurrWeaponIndex) == EWeaponType::Unarmed)
		WeaponDatas[PrevWeaponIndex]->GetEquipment()->UnEquip();
	else
		WeaponDatas[PrevWeaponIndex]->GetEquipment()->EndUnEquip();
}

