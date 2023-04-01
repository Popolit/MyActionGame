#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponAttachment.generated.h"

DECLARE_DELEGATE_TwoParams(FOnWeaponAttachmentOverlap, AActor*, AActor*);
DECLARE_DELEGATE(FOnWeaponAttachmentCollision)


//Weapon Attachment, Collisions
UCLASS(BlueprintType)
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
	
	void EndEquip();
	void EndUnEquip();

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
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
	FOnWeaponAttachmentOverlap OnWeaponAttachmentBeginOverlap;
	FOnWeaponAttachmentOverlap OnWeaponAttachmentEndOverlap;
	FOnWeaponAttachmentCollision OnWeaponAttachmentOnCollision;
	FOnWeaponAttachmentCollision OnWeaponAttachmentOffCollision;
};
