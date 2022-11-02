#include "CWeapon_Ranged_Shotgun.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"

ACWeapon_Ranged_Shotgun::ACWeapon_Ranged_Shotgun()
{
    USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Weapon/Shotgun/Shotgun_B.Shotgun_B'");
	Mesh->SetSkeletalMesh(mesh);

    HolsterSocketName = "HolsterShotgunSocket";

}

void ACWeapon_Ranged_Shotgun::BeginPlay()
{
    Super::BeginPlay();
    this->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocketName);
}