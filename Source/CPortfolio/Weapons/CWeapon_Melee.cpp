#include "CWeapon_Melee.h"
#include "Global.h"


ACWeapon_Melee::ACWeapon_Melee()
{
    CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Root);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
