#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponAttachment.generated.h"

/* Weapon Attachment */
UCLASS(BlueprintType)
class WEAPONSTRUCTURE_API AWeaponAttachment : public AActor
{
	GENERATED_BODY()
public:	
	AWeaponAttachment();
	
protected:
	virtual void BeginPlay() override;
	
	void EndEquip();
	void EndUnEquip();

protected:
	void AttachTo(FName InSocketName);
	
protected:
	UPROPERTY()
		ACharacter* OwnerCharacter;
	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly)
		FName HolsterSocketName;

	UPROPERTY(EditDefaultsOnly)
		FName EquipSocketName;
	
	UPROPERTY()
		TArray<UShapeComponent*> Collisions;
};
