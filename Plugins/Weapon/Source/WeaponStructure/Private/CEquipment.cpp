#include "CEquipment.h"
/*#include "CEquipment.h"
#include "CHelpers.h"
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


void UCEquipment::Equip()
{
	bBeginEquip = true;
	State->SetEquipMode();

	if (EquipData.bCanMove == false)
		Status->Stop();
	if (EquipData.Montage != nullptr)
		OwnerCharacter->PlayAnimMontage(EquipData.Montage, EquipData.PlayRatio);
	else
		EndEquip();

	if (EquipData.bUseControlRotation)
		Status->EnableControlRotation();
}


void UCEquipment::EndEquip()
{
	bEquipping = true;
	bBeginEquip = false;

	State->SetIdleMode();
	Status->Move();

	if(OnEndEquip.IsBound())
		OnEndEquip.Broadcast();
}

void UCEquipment::UnEquip()
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

void UCEquipment::EndUnEquip()
{
	bEquipping = false;
	bBeginUnEquip = false;
	Status->DisableControlRotation();
	

	State->SetIdleMode();
	Status->Move();
	
	if(OnEndUnEquip.IsBound())
		OnEndUnEquip.Broadcast();
}*/