#include "CAN_EndUnEquip.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CWeaponComponent.h"

FString UCAN_EndUnEquip::GetNotifyName_Implementation() const
{
    return "EndUnEquip";
}

void UCAN_EndUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    ACCharacter_Base* Character = Cast<ACCharacter_Base>(MeshComp->GetOwner());
    CheckNull(Character);

    UCWeaponComponent* Weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
    CheckNull(Weapon);

    Weapon->EndUnEquip();
}