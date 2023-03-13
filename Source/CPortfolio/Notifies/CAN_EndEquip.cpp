#include "CAN_EndEquip.h"
#include "CHelpers.h"
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
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());
    UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
    CheckNull(weapon);
	/*CheckNull(weapon->GetEquipment());
    weapon->GetEquipment()->EndEquip();*/
}