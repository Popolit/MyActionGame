#include "CEquipment.h"
#include "Global.h"
#include "Animation/CAnimInstance.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"


void UCEquipment::BeginPlay(class ACCharacter_Base* InOwner, const FEquipData& InEquipData, const FUnEquipData& InUnEquipData)
{
	OwnerCharacter = InOwner;
	EquipData = InEquipData;
	UnEquipData = InUnEquipData;

	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
}


//  *********************
//     Equip, UnEquip
//  *********************
void UCEquipment::Equip_Implementation()
{
	bBeginEquip = true;
	State->SetEquipMode();

	if (EquipData.bCanMove == false)
		Status->Stop();
	if (!!EquipData.Montage)
		OwnerCharacter->PlayAnimMontage(EquipData.Montage, EquipData.PlayRatio);
	else
		EndEquip();

	if (EquipData.bUseControlRotation)
		Status->EnableControlRotation();
}


void UCEquipment::EndEquip_Implementation()
{
	bEquipping = true;
	bBeginEquip = false;

	State->SetIdleMode();
	Status->Move();

	if(OnEndEquip.IsBound())
		OnEndEquip.Broadcast();
}

void UCEquipment::UnEquip_Implementation()
{
	bBeginUnEquip = true;
	State->SetEquipMode();
	
	if (!!UnEquipData.Montage)
		OwnerCharacter->PlayAnimMontage(UnEquipData.Montage, UnEquipData.PlayRatio);
	else
		EndUnEquip();

	if (EquipData.bUseControlRotation)
		Status->EnableControlRotation();
}

void UCEquipment::EndUnEquip_Implementation()
{
	bEquipping = false;
	bBeginUnEquip = false;
	Status->DisableControlRotation();
	

	State->SetIdleMode();
	Status->Move();
	
	if(OnEndUnEquip.IsBound())
		OnEndUnEquip.Broadcast();
}