#pragma once

#include "CoreMinimal.h"
#include "WeaponAttachment.h"
#include "Engine/DataAsset.h"
#include "WeaponAsset.generated.h"

class UWeapon;
class UActionAsset;

//Create Weapon Class
UCLASS()
class WEAPONSTRUCTURE_API UWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
private:
	UWeaponAsset();

public:
	void BeginPlay(AActor* InOwner, UWeapon** OutWeaponData);

private:
	UPROPERTY(EditAnywhere, Category="Attachment")
		TArray<TSubclassOf<AWeaponAttachment>> AttachmentClasses;
	UPROPERTY(EditAnywhere, Category="CameraControl")
		bool bUseControlRotation;
	UPROPERTY(EditAnywhere, Category="Action")
		UActionAsset* ActionDataAsset;

public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
