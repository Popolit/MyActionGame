#include "WeaponAsset.h"

#include "Weapon.h"
#include "ActionAsset.h"

UWeaponAsset::UWeaponAsset()
{
}

//Weapon Asset을 이용해 Weapon 객체를 생성
void UWeaponAsset::BeginPlay(ACharacter* InOwnerCharacter, UWeapon** OutWeapon)
{
	//Weapon 객체 생성
	*OutWeapon = NewObject<UWeapon>();

	//Weapon의 오너 캐릭터 설정
	(*OutWeapon)->OwnerCharacter = InOwnerCharacter;


	//Attachment 생성
	for(TSubclassOf<AWeaponAttachment> AttachmentClass : AttachmentClasses)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = InOwnerCharacter;
		
		(*OutWeapon)->Attachments.Push(InOwnerCharacter->GetWorld()->SpawnActor<AWeaponAttachment>(AttachmentClass, ActorSpawnParams));
	}

	//Weapon의 값 셋팅
	(*OutWeapon)->bUseControlRotation = bUseControlRotation;
	(*OutWeapon)->EquipMontage = EquipMontage;
	(*OutWeapon)->UnEquipMontage = UnEquipMontage;
	(*OutWeapon)->AnimClass = AnimClass;

	
	if(ActionDataAsset == nullptr)
	{
		return;
	}

	//액션 애셋 세팅
	ActionDataAsset->BeginPlay(&(*OutWeapon)->Actions, InOwnerCharacter);
}

//Edit창에서 변화가 일어났을 때(Weapon Editor가 있기 때문에 오버로딩)
void UWeaponAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(FApp::IsGame())
	{
		return;
	}

	//Refresh할 필요가 있는지
	bool bRefresh = false;
	bRefresh |= (PropertyChangedEvent.GetPropertyName().Compare("AttackDatas") == 0);
	bRefresh |= (PropertyChangedEvent.GetPropertyName().Compare("HitDatas") == 0);

	//Refresh가 필요할 경우
	if (bRefresh)
	{
		//Array의 내용이 변했는지 체크
		bool bCheck = false;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate;
		bCheck |= PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear;
		
		if (bCheck)
		{
			//WeaponEditorDetailsView를 찾아 갱신
			FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.FindDetailView("WeaponEditorDetailsView");
			if(DetailsView.IsValid())
			{
				DetailsView->ForceRefresh();
			}
		}
	}
}