#include "CAN_EndEquip.h"
#include "CHelpers.h"
#include "Weapon.h"
#include "Components/CWeaponComponent.h"

UCAN_EndEquip::UCAN_EndEquip() : NotifyName("EndEquip")
{
}

FString UCAN_EndEquip::GetNotifyName_Implementation() const
{
    return NotifyName;
}

void UCAN_EndEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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
	WeaponComponent->GetWeapon()->EndEquip();
}