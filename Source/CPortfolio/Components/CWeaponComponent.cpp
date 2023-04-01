#include "CWeaponComponent.h"
#include "CHelpers.h"
#include "WeaponAsset.h"
#include "Weapon.h"

#include "Characters/CCharacter_Base.h"


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

	check(Weapons[0]);
	CurrWeapon = Weapons[0];
	PrevWeapon = CurrWeapon;
}


void UCWeaponComponent::ChangeWeapon(int const& Index)
{
	if (!Weapons.IsValidIndex(Index))
	{
		return;
	}

	PrevWeapon = CurrWeapon;
	CurrWeapon = Weapons[Index];

	//Weapon -> Unarmed
	if(PrevWeapon == CurrWeapon)
	{
		PrevWeapon->UnEquip();
		CurrWeapon = Weapons[0];
	}

	//WeaponA -> WeaponB : Immediate UnEquip
	else if(PrevWeapon != Weapons[0])
	{
		PrevWeapon->EndUnEquip();
	}
	//EquipWeapon
	CurrWeapon->Equip();

	if(CurrWeapon->GetAnimClass() != nullptr)
	{
		OwnerCharacter->GetMesh()->LinkAnimGraphByTag("Weapon", CurrWeapon->GetAnimClass());
		OwnerCharacter->GetMesh()->GetLinkedAnimGraphInstanceByTag("Weapon")->NativeBeginPlay();
	}
	
	if(OnWeaponChanged.IsBound())
	{
		OnWeaponChanged.Broadcast(PrevWeapon, CurrWeapon);
	}
}
