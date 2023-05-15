#pragma once

#include "CoreMinimal.h"
#include "WeaponAttachment.h"
#include "Interfaces/CI_Collision.h"
#include "CWeaponAttachment_Projectile.generated.h"

DECLARE_DELEGATE_TwoParams(FOnWeaponAttachmentOverlap, AActor*, AActor*);
DECLARE_DELEGATE(FOnWeaponAttachmentCollision)


/* Weapon Attachment Has Collisions */
UCLASS(BlueprintType)
class CPORTFOLIO_API ACWeaponAttachment_Collision : public AWeaponAttachment, public ICI_Collision
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
public:
	void EnableCollision();
	void DisableCollision();
	
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:	
	UPROPERTY()
	TArray<UShapeComponent*> Collisions;
	
public:
	FOnWeaponAttachmentOverlap OnWeaponAttachmentBeginOverlap;
	FOnWeaponAttachmentOverlap OnWeaponAttachmentEndOverlap;
	FOnWeaponAttachmentCollision OnWeaponAttachmentOnCollision;
	FOnWeaponAttachmentCollision OnWeaponAttachmentOffCollision;
};
