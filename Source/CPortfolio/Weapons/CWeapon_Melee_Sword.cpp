#include "CWeapon_Melee_Sword.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"

ACWeapon_Melee_Sword::ACWeapon_Melee_Sword()
{
    UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Weapon/Sword/Meshes/SM_Sword.SM_Sword'");
	Mesh->SetStaticMesh(mesh);

    HolsterSocketName = "HolsterSwordSocket";
}

void ACWeapon_Melee_Sword::BeginPlay()
{
    Super::BeginPlay();
    this->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocketName);

}