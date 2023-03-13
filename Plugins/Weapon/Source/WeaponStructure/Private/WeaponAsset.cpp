#include "WeaponAsset.h"

#include "Weapon.h"

UWeaponAsset::UWeaponAsset()
{
}

void UWeaponAsset::BeginPlay(AActor* InOwner, UWeapon** OutWeaponData)
{
	*OutWeaponData = NewObject<UWeapon>();
	for(TSubclassOf<AWeaponAttachment> AttachmentClass : AttachmentClasses)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = InOwner;
		
		(*OutWeaponData)->Attachments.Push(InOwner->GetWorld()->SpawnActor<AWeaponAttachment>(AttachmentClass, ActorSpawnParams));
	}

	(*OutWeaponData)->bUseControlRotation = bUseControlRotation;
	
	/*
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
	ActionDataAsset->BeginPlay(InOwner, &(*OutWeaponData)->ActionData);*/
}

void UWeaponAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(FApp::IsGame())
	{
		return;
	}

	
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
			{
				detailsView->ForceRefresh();
			}
		}
	}
}