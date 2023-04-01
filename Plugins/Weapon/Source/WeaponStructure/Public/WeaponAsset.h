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
	void BeginPlay(ACharacter* InOwnerCharacter, UWeapon** OutWeaponData);

private:
	UPROPERTY(EditAnywhere, Category="Attachment")
		TArray<TSubclassOf<AWeaponAttachment>> AttachmentClasses;
	
	UPROPERTY(EditAnywhere, Category="CameraControl")
		bool bUseControlRotation;
	
	UPROPERTY(EditDefaultsOnly, Category="Equip")
		UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category="Equip")
		UAnimMontage* UnEquipMontage;
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
		TSubclassOf<UAnimInstance> AnimClass;
	
	UPROPERTY(EditAnywhere, Category="Action")
		UActionAsset* ActionDataAsset;
	
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
