#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	FORCEINLINE TSubclassOf<UAnimInstance> GetAnimClass() const { return AnimClass; }
	FORCEINLINE UActionSet* GetActionSet() const { return Actions; }
	
public:
	void Equip() const;
	void UnEquip() const;
	void EndEquip() const;
	void EndUnEquip() const;
	
	void OnCollision() const;
	void OffCollision() const;
public:
	void EndPlay(AActor* InOwner);
	
private:
	UPROPERTY()
		ACharacter* OwnerCharacter;
	
	UPROPERTY()
		TArray<AWeaponAttachment*> Attachments;

	UPROPERTY()
		TSubclassOf<UAnimInstance> AnimClass;
	
	UPROPERTY()
		bool bUseControlRotation;
	
	UPROPERTY()
		UAnimMontage* EquipMontage;

	UPROPERTY()
		UAnimMontage* UnEquipMontage;
	
	UPROPERTY()
		UActionSet* Actions;
};


