#include "CWeaponComponent.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Weapons/CWeapon.h"


//  *********************
//      기본 세팅
//  *********************
UCWeaponComponent::UCWeaponComponent()
{
	WeaponType = EWeaponType::Max;
}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	//오너 캐릭터 세팅
	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner);

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//무기 세팅
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
	//무기를 장착함
	if(WeaponType != EWeaponType::Max)
	{
		//무기 해제
		if(WeaponType == WeaponList[Index]->GetType())
		{
			UnEquip();
			return;
		}

		//무기 교체 시 즉시 UnEquip 종료
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
