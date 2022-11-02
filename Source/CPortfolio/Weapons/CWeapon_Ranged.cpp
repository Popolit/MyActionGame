#include "CWeapon_Ranged.h"
#include "Global.h"

ACWeapon_Ranged::ACWeapon_Ranged()
{
    CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", Root);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
