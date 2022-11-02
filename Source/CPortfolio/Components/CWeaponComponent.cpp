#include "CWeaponComponent.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Weapons/CWeapon.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACPlayer>(GetOwner());
	CheckNull(Owner);

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	for (TSubclassOf<ACWeapon> weaponClass : WeaponClasses)
	{
		if (!!weaponClass)
		{
			ACWeapon* weapon = Owner->GetWorld()->SpawnActor<ACWeapon>(weaponClass, params);
			Weapons.Add(weapon);
		}
	}
}


void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

