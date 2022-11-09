#include "CAN_EndEquip.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CWeaponComponent.h"

FString UCAN_EndEquip::GetNotifyName_Implementation() const
{
    return "EndEquip";
}

void UCAN_EndEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    ACCharacter_Base* Character = Cast<ACCharacter_Base>(MeshComp->GetOwner());
    CheckNull(Character);

    UCWeaponComponent* Weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
    CheckNull(Weapon);

    Weapon->EndEquip();
}