#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapon.generated.h"

class UActionSet;
class AWeaponAttachment;

UCLASS()
class WEAPONSTRUCTURE_API UWeapon : public UObject
{
	GENERATED_BODY()
	friend class UWeaponAsset;
public:
	void Equip();
	void UnEquip();
	void EndEquip();
	void EndUnEquip();
	
	void OnCollision();
	void OffCollision();
public:
	void EndPlay(AActor* InOwner);
	
private:
	UPROPERTY()
		TArray<AWeaponAttachment*> Attachments;
	
	UPROPERTY()
		bool bUseControlRotation;
	
	UPROPERTY()
		UActionSet* Actions;
};


