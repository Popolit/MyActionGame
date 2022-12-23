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
    ACCharacter_Base* character = Cast<ACCharacter_Base>(MeshComp->GetOwner());
    CheckNull(character);

    UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
    CheckNull(weapon);
	CheckNull(weapon->GetEquipment());
    weapon->GetEquipment()->EndEquip();
}