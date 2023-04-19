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
	//실제 무기의 외형
	UPROPERTY(EditAnywhere, Category="Attachment")
		TArray<TSubclassOf<AWeaponAttachment>> AttachmentClasses;

	//true일 경우 카메라의 방향을 캐릭터 방향 시점으로 고정
	UPROPERTY(EditAnywhere, Category="CameraControl")
		bool bUseControlRotation;
	
	UPROPERTY(EditDefaultsOnly, Category="Equip")
		UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category="Equip")
		UAnimMontage* UnEquipMontage;

	//무기에 대한 캐릭터 애니메이션 클래스
	UPROPERTY(EditDefaultsOnly, Category="Animation")
		TSubclassOf<UAnimInstance> AnimClass;

	//액션 데이터 애셋
	UPROPERTY(EditAnywhere, Category="Action")
		UActionAsset* ActionDataAsset;
	
public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
