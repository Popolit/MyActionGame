#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void UCEquipment::BeginPlay(class ACharacter* InOwner, const FEquipData& InEquipData, const FUnequipData& InUnequipData)
{
	OwnerCharacter = InOwner;
	EquipData = InEquipData;
	UnequipData = InUnequipData;

	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}


//  *********************
//     Equip, Unequip
//  *********************
void UCEquipment::Equip_Implementation()
{
	State->SetEquipMode();

	if (EquipData.bCanMove == false)
		Status->Stop();
	if (!!EquipData.Montage)
		OwnerCharacter->PlayAnimMontage(EquipData.Montage, EquipData.PlayRatio);
	else
	{
		Begin_Equip();
		End_Equip();
	}

	if (EquipData.bUseControlRotation)
		Status->EnableControlRotation();
}

void UCEquipment::Begin_Equip_Implementation()
{
	bBeginEquip = true;

	if (OnEquip.IsBound())
		OnEquip.Broadcast();
}

void UCEquipment::End_Equip_Implementation()
{
	bEquipping = true;
	bBeginEquip = false;

	State->SetIdleMode();
	Status->Move();
}

void UCEquipment::Unequip_Implementation()
{
	bEquipping = false;
	Status->DisableControlRotation();

	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}