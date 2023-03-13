#include "CWeaponComponent.h"
#include "CHelpers.h"
#include "WeaponAsset.h"
#include "Weapon.h"

#include "Characters/Player/CPlayer.h"


UCWeaponComponent::UCWeaponComponent()
{
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	check(OwnerCharacter);

	//Weapon ¼¼ÆÃ
	for(UWeaponAsset* Weapon : WeaponAssets)
	{
		UWeapon* NewWeaponData;
		Weapon->BeginPlay(OwnerCharacter, &NewWeaponData);
		Weapons.Push(NewWeaponData);
	}
	
	CurrWeapon = nullptr;
}


void UCWeaponComponent::ChangeWeapon(int const& Index)
{
	if (!Weapons.IsValidIndex(Index))
	{
		return;
	}

	UWeapon* PrevWeapon = CurrWeapon;
	CurrWeapon = Weapons[Index];

	//Weapon -> Unarmed
	if(PrevWeapon == CurrWeapon)
	{
		PrevWeapon->UnEquip();
		CurrWeapon = nullptr;
	}

	//WeaponA -> WeaponB : Immediate UnEquip
	else if(PrevWeapon != nullptr)
	{
		PrevWeapon->EndEquip();
	}
	//EquipWeapon
	CurrWeapon->Equip();
	
	/*if(OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast();*/
}
