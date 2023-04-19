#include "WeaponAsset.h"

#include "Weapon.h"
#include "ActionAsset.h"

UWeaponAsset::UWeaponAsset()
{
}

//Weapon Asset�� �̿��� Weapon ��ü�� ����
void UWeaponAsset::BeginPlay(ACharacter* InOwnerCharacter, UWeapon** OutWeapon)
{
	//Weapon ��ü ����
	*OutWeapon = NewObject<UWeapon>();

	//Weapon�� ���� ĳ���� ����
	(*OutWeapon)->OwnerCharacter = InOwnerCharacter;


	//Attachment ����
	for(TSubclassOf<AWeaponAttachment> AttachmentClass : AttachmentClasses)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = InOwnerCharacter;
		
		(*OutWeapon)->Attachments.Push(InOwnerCharacter->GetWorld()->SpawnActor<AWeaponAttachment>(AttachmentClass, ActorSpawnParams));
	}

	//Weapon�� �� ����
	(*OutWeapon)->bUseControlRotation = bUseControlRotation;
	(*OutWeapon)->EquipMontage = EquipMontage;
	(*OutWeapon)->UnEquipMontage = UnEquipMontage;
	(*OutWeapon)->AnimClass = AnimClass;

	
	if(ActionDataAsset == nullptr)
	{
		return;
	}

	//�׼� �ּ� ����
	ActionDataAsset->BeginPlay(&(*OutWeapon)->Actions, InOwnerCharacter);
}

//Editâ���� ��ȭ�� �Ͼ�� ��(Weapon Editor�� �ֱ� ������ �����ε�)
void UWeaponAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(FApp::IsGame())
	{
		return;
	}

	//Refresh�� �ʿ䰡 �ִ���
	bool bRefresh = false;
	bRefresh |= (PropertyChangedEvent.GetPropertyName().Compare("AttackDatas") == 0);
	bRefresh |= (PropertyChangedEvent.GetPropertyName().Compare("HitDatas") == 0);

	//Refresh�� �ʿ��� ���
	if (bRefresh)
	{
		//Array�� ������ ���ߴ��� üũ
		bool bCheck = false;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear;
		
		if (bCheck)
		{
			//WeaponEditorDetailsView�� ã�� ����
			FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.FindDetailView("WeaponEditorDetailsView");
			if(DetailsView.IsValid())
			{
				DetailsView->ForceRefresh();
			}
		}
	}
}