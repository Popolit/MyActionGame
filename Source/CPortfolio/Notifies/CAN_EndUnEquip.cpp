#include "CAN_EndUnEquip.h"
#include "CHelpers.h"

#include "Weapon.h"
#include "Components/CWeaponComponent.h"

UCAN_EndUnEquip::UCAN_EndUnEquip() : NotifyName("EndUnEquip")
{
}

FString UCAN_EndUnEquip::GetNotifyName_Implementation() const
{
    return NotifyName;
}

void UCAN_EndUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if(MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
    {
        return;
    }
    const UCWeaponComponent *WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());

    if(WeaponComponent == nullptr)
    {
        return;
    }
    WeaponComponent->GetPrevWeapon()->EndUnEquip();
}