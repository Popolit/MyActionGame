#include "CWeapon.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<ACCharacter_Base>(GetOwner());
	CheckNull(Owner);
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

