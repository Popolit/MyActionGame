#pragma once

#include "CoreMinimal.h"
#include "CAttachment.h"
#include "Engine/DataAsset.h"
#include "CWeaponStructure.h"
#include "CWeaponAsset.generated.h"


UCLASS()
class CPORTFOLIO_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	friend class UCWeaponComponent;

private:
	UPROPERTY(EditAnywhere)
		EWeaponType Type;
	
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class ACAttachment>> AttachmentClasses;
	
	UPROPERTY(EditAnywhere, Category="Equip")
		FEquipData EquipData;
	
	UPROPERTY(EditAnywhere, Category="Equip")
		FUnEquipData UnEquipData;
	
	UPROPERTY(EditAnywhere, Category="Action")
		class UCActionAsset* ActionDataAsset;

private:
	UCWeaponAsset();

	void BeginPlay(class ACCharacter_Base* InOwner, class UCWeapon** OutWeaponData);

public:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
};
