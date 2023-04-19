#include "CWeaponComponent.h"
#include "CHelpers.h"
#include "WeaponAsset.h"
#include "Weapon.h"

#include "Characters/CCharacter_Base.h"
#include "Interfaces/CI_EventHandler.h"
#include "Interfaces/CI_WeaponHasFABRIK.h"


UCWeaponComponent::UCWeaponComponent()
{
}

//���� �� OnwerCharacter�� Weapon ����
void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	check(OwnerCharacter);

	//Weapon ����
	for(UWeaponAsset* Weapon : WeaponAssets)
	{
		UWeapon* NewWeaponData;
		Weapon->BeginPlay(OwnerCharacter, &NewWeaponData);
		Weapons.Push(NewWeaponData);
	}

	check(Weapons[0]);
	CurrWeapon = Weapons[0];
	PrevWeapon = CurrWeapon;

	CheckWeaponHasFABRIK();
}

/**
 * ���� ��ü ��ư�� ������ ��, �ش� ��ȣ�� ����� ��ü
 * @param Index Weapon�� ��� ��ȣ
 */
void UCWeaponComponent::ChangeWeapon(int const& Index)
{
	if (!Weapons.IsValidIndex(Index))
	{
		return;
	}

	PrevWeapon = CurrWeapon;
	CurrWeapon = Weapons[Index];

	//Weapon -> Unarmed
	if(PrevWeapon == CurrWeapon)
	{
		PrevWeapon->UnEquip();
		CurrWeapon = Weapons[0];
	}

	//WeaponA -> WeaponB : Immediate UnEquip
	else if(PrevWeapon != Weapons[0])
	{
		PrevWeapon->EndUnEquip();
	}
	//EquipWeapon
	CurrWeapon->Equip();

	if(CurrWeapon->GetAnimClass() != nullptr)
	{
		OwnerCharacter->GetMesh()->LinkAnimGraphByTag("Weapon", CurrWeapon->GetAnimClass());
		OwnerCharacter->GetMesh()->GetLinkedAnimGraphInstanceByTag("Weapon")->NativeBeginPlay();
	}

	if(OnWeaponChanged.IsBound())
	{
		OnWeaponChanged.Broadcast(PrevWeapon, CurrWeapon);
	}

	CheckWeaponHasFABRIK();
}

/* WeaponEvent ��� */
void UCWeaponComponent::BindWeaponEvent(FName const& InEventName, ICI_EventHandler* InEventHandler)
{
	WeaponEvents.Add(InEventName, Cast<UObject>(InEventHandler));
}


/**
 * Weapon ���� �̺�Ʈ �߻�
 * @param InEventName �̺�Ʈ �̸�
 */
void UCWeaponComponent::OnWeaponEvent(FName const& InEventName)
{
	if(WeaponEvents.Contains(InEventName))
	{
		ICI_EventHandler* EventHandler = Cast<ICI_EventHandler>(WeaponEvents[InEventName]);
		if(EventHandler != nullptr)
		{
			EventHandler->HandleEvent();
		}
	}
}

/**
 * ���Ⱑ FABRIK�� �ʿ��� Attachment�� �������� Ȯ���ϰ�
 * FABRIK�̸� �ִ� �ν��Ͻ��� ����
 */
void UCWeaponComponent::CheckWeaponHasFABRIK()
{
	//FABRIK�� �ʿ��� ���ⱺ (Ȱ, ���� ��)�� ���
	bool bFABRIKWeapon = false;
	AWeaponAttachment* AttachmentHasFABRIK = nullptr;
	for(AWeaponAttachment* Attachment : CurrWeapon->GetAttachments())
	{
		if(Attachment == nullptr)
		{
			continue;
		}

		if(Attachment->GetClass()->ImplementsInterface(UCI_WeaponHasFABRIK::StaticClass()))
		{
			bFABRIKWeapon = true;
			AttachmentHasFABRIK = Attachment;
			break;
		}
	}

	if(OnFABRIKWeapon.IsBound())
	{
		OnFABRIKWeapon.Execute(bFABRIKWeapon, AttachmentHasFABRIK);
	}
}
