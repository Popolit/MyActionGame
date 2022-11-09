#include "CWeaponAsset.h"
#include "Global.h"

#include "CWeaponAsset.h"
#include "Actions/CAttack.h"
#include "Actions/CSubAction.h"
#include "CWeaponData.h"

#include "GameFramework/Character.h"


UCWeaponAsset::UCWeaponAsset()
{
	AttackClass = UCAttack::StaticClass();
}

void UCWeaponAsset::BeginPlay(ACharacter* InOwner, UCWeaponData** OutWeaponData)
{
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