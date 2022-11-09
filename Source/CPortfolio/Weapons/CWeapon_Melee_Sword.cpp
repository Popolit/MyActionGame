#include "CWeapon_Melee_Sword.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"
#include "Weapons/CWeaponAsset.h"

ACWeapon_Melee_Sword::ACWeapon_Melee_Sword()
{
    UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Weapon/Sword/Meshes/SM_Sword.SM_Sword'");
	Mesh->SetStaticMesh(mesh);

    Type = EWeaponType::Sword;
}

void ACWeapon_Melee_Sword::BeginPlay()
{
    Super::BeginPlay();
}

void ACWeapon_Melee_Sword::EndEquip()
{
    Super::EndEquip();
    
}

