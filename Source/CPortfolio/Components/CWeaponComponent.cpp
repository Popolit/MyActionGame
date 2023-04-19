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

//시작 시 OnwerCharacter와 Weapon 세팅
void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());
	check(OwnerCharacter);

	//Weapon 세팅
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
 * 무기 교체 버튼을 눌렀을 때, 해당 번호의 무기로 교체
 * @param Index Weapon의 등록 번호
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

/* WeaponEvent 등록 */
void UCWeaponComponent::BindWeaponEvent(FName const& InEventName, ICI_EventHandler* InEventHandler)
{
	WeaponEvents.Add(InEventName, Cast<UObject>(InEventHandler));
}


/**
 * Weapon 관련 이벤트 발생
 * @param InEventName 이벤트 이름
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
 * 무기가 FABRIK가 필요한 Attachment를 가졌는지 확인하고
 * FABRIK이면 애님 인스턴스에 전달
 */
void UCWeaponComponent::CheckWeaponHasFABRIK()
{
	//FABRIK이 필요한 무기군 (활, 샷건 등)인 경우
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
