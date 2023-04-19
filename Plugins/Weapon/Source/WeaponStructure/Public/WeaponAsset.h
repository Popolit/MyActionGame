#pragma once

#include "CoreMinimal.h"
#include "WeaponAttachment.h"
#include "Engine/DataAsset.h"
#include "WeaponAsset.generated.h"

class UWeapon;
class UActionAsset;

/* Asset to create Weapon Class */
UCLASS()
class WEAPONSTRUCTURE_API UWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
private:
	UWeaponAsset();

public:
	void BeginPlay(ACharacter* InOwnerCharacter, UWeapon** OutWeapon);

private:
	//���� ������ ����
	UPROPERTY(EditAnywhere, Category="Attachment")
		TArray<TSubclassOf<AWeaponAttachment>> AttachmentClasses;

	//true�� ��� ī�޶��� ������ ĳ���� ���� �������� ����
	UPROPERTY(EditAnywhere, Category="CameraControl")
		bool bUseControlRotation;
	
	UPROPERTY(EditDefaultsOnly, Category="Equip")
		UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category="Equip")
		UAnimMontage* UnEquipMontage;

	//���⿡ ���� ĳ���� �ִϸ��̼� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category="Animation")
		TSubclassOf<UAnimInstance> AnimClass;

	//�׼� ������ �ּ�
	UPROPERTY(EditAnywhere, Category="Action")
		UActionAsset* ActionDataAsset;
	
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
