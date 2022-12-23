#include "CWeaponAsset.h"
#include "Global.h"

#include "CWeapon.h"
#include "CEquipment.h"

#include "Characters/CCharacter_Base.h"
#include "Weapons/Actions/CActionAsset.h"


UCWeaponAsset::UCWeaponAsset()
{
}

void UCWeaponAsset::BeginPlay(ACCharacter_Base* InOwner, UCWeapon** OutWeaponData)
{
	*OutWeaponData = NewObject<UCWeapon>();
	for(TSubclassOf<ACAttachment> attachmentclass : AttachmentClasses)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		(*OutWeaponData)->Attachments.Emplace(InOwner->GetWorld()->SpawnActor<ACAttachment>(attachmentclass, params));
	}

	UCEquipment* equipment = nullptr;
	
	equipment = NewObject<UCEquipment>(this);
	equipment->BeginPlay(InOwner, EquipData, UnEquipData);

	for (ACAttachment* attachment : (*OutWeaponData)->Attachments)
	{
		equipment->OnEndEquip.AddUObject(attachment, &ACAttachment::OnEndEquip);
		equipment->OnEndUnEquip.AddUObject(attachment, &ACAttachment::OnEndUnEquip);
	}
	
	(*OutWeaponData)->Equipment = equipment;
	(*OutWeaponData)->Type = Type;

	CheckNull(ActionDataAsset);
	ActionDataAsset->BeginPlay(InOwner, &(*OutWeaponData)->ActionData);
}

void UCWeaponAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	CheckTrue(FApp::IsGame());

	
	bool bRefresh = false;
	bRefresh |= (PropertyChangedEvent.GetPropertyName().Compare("AttackDatas") == 0);
	bRefresh |= (PropertyChangedEvent.GetPropertyName().Compare("HitDatas") == 0);

	if (bRefresh)
	{
		bool bCheck = false;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear;

		if (bCheck)
		{
			FPropertyEditorModule& propertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			TSharedPtr<IDetailsView> detailsView = propertyEditor.FindDetailView("WeaponEditorDetailsView");
			
			if(detailsView.IsValid())
				detailsView->ForceRefresh();
		}
	}
}