#include "CWeaponComponent.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Weapons/CWeapon.h"


//  *********************
//      �⺻ ����
//  *********************
UCWeaponComponent::UCWeaponComponent()
{
	WeaponType = EWeaponType::Max;
}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//���� ĳ���� ����
	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner);

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//���� ����
	for (TSubclassOf<ACWeapon> weaponClass : WeaponClasses)
	{
		if (!!weaponClass)
		{
			ACWeapon* weapon = Owner->GetWorld()->SpawnActor<ACWeapon>(weaponClass, params);
			WeaponList.Add(weapon);
		}
	}
}



//  *********************
//      Equip
//  *********************
void UCWeaponComponent::Equip(uint8 const& Index)
{
	CheckNull(WeaponList[Index]);
	//���⸦ ������
	if(WeaponType != EWeaponType::Max)
	{
		//���� ����
		if(WeaponType == WeaponList[Index]->GetType())
		{
			UnEquip();
			return;
		}

		//���� ��ü �� ��� UnEquip ����
		EndUnEquip();
	}
	
	CurrWeapon = WeaponList[Index];
	WeaponType = CurrWeapon->GetType();
	CurrWeapon->Equip();
}

void UCWeaponComponent::EndEquip() const
{
	CheckNull(CurrWeapon);

	CurrWeapon->EndEquip();
	if(OnWeaponChanged.IsBound())
		OnWeaponChanged.Broadcast(CurrWeapon->GetType());
}
void UCWeaponComponent::UnEquip() const
{
	CheckNull(CurrWeapon);

	CurrWeapon->UnEquip();
}

void UCWeaponComponent::EndUnEquip() 
{
	CheckNull(CurrWeapon);

	CurrWeapon->EndUnEquip();
	CurrWeapon = nullptr;
	if(OnWeaponChanged.IsBound())
		OnWeaponChanged.Broadcast(EWeaponType::Max);
}
