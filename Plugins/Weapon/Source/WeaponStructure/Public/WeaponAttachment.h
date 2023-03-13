#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponAttachment.generated.h"

DECLARE_DELEGATE_ThreeParams(FWeaponAttachmentOverlap, ACharacter*,  AActor*, AActor*);
DECLARE_DELEGATE(FWeaponAttachmentCollision)


//Weapon Attachment, Collisions
UCLASS()
class WEAPONSTRUCTURE_API AWeaponAttachment : public AActor
{
	GENERATED_BODY()
public:	
	AWeaponAttachment();
protected:
	virtual void BeginPlay() override;

public:
	void OnCollision();
	void OffCollision();

	void OnEndEquip();
	void OnEndUnEquip();

private:
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
	
public:
	FWeaponAttachmentOverlap OnWeaponAttachmentBeginOverlap;
	FWeaponAttachmentOverlap OnWeaponAttachmentEndOverlap;
	FWeaponAttachmentCollision OnWeaponAttachmentCollision;
	FWeaponAttachmentCollision OffWeaponAttachmentCollision;
};
