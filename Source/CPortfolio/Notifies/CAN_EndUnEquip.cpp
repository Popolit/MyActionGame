#include "CAN_EndUnEquip.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CEquipment.h"

FString UCAN_EndUnEquip::GetNotifyName_Implementation() const
{
    return "EndUnEquip";
}

void UCAN_EndUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());
    UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
    CheckNull(weapon);
    CheckNull(weapon->GetPrevEquipment());

    weapon->GetPrevEquipment()->EndUnEquip();
}