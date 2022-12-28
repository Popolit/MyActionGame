#include "CAN_EndEquip.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CEquipment.h"

FString UCAN_EndEquip::GetNotifyName_Implementation() const
{
    return "EndEquip";
}

void UCAN_EndEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());
    UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
    CheckNull(weapon);
	CheckNull(weapon->GetEquipment());
    weapon->GetEquipment()->EndEquip();
}