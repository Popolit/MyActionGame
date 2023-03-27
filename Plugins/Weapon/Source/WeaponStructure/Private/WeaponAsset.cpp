#include "WeaponAsset.h"

#include "Weapon.h"
#include "ActionAsset.h"

UWeaponAsset::UWeaponAsset()
{
}

void UWeaponAsset::BeginPlay(ACharacter* InOwnerCharacter, UWeapon** OutWeaponData)
{
	*OutWeaponData = NewObject<UWeapon>();

	(*OutWeaponData)->OwnerCharacter = InOwnerCharacter;
	
	for(TSubclassOf<AWeaponAttachment> AttachmentClass : AttachmentClasses)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = InOwnerCharacter;
		
		(*OutWeaponData)->Attachments.Push(InOwnerCharacter->GetWorld()->SpawnActor<AWeaponAttachment>(AttachmentClass, ActorSpawnParams));
	}

	(*OutWeaponData)->bUseControlRotation = bUseControlRotation;
	(*OutWeaponData)->EquipMontage = EquipMontage;
	(*OutWeaponData)->UnEquipMontage = UnEquipMontage;
	(*OutWeaponData)->AnimClass = AnimClass;
	
	if(ActionDataAsset == nullptr)
	{
		return;
	}
	ActionDataAsset->BeginPlay(&(*OutWeaponData)->Actions, InOwnerCharacter);
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