#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);

//무기의 외형, Collision Box 클래스
UCLASS()
class CPORTFOLIO_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
		FName HolsterSocketName;

	UPROPERTY(EditAnywhere)
		FName HandSocketName;


public:	
	ACAttachment();

	void OnCollision();
	void OffCollision();

	void OnEndEquip();
	void OnEndUnEquip();
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);

public:
	FAttachmentOverlap OnAttachmentBeginOverlap;
	FAttachmentOverlap OnAttachmentEndOverlap;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACCharacter_Base* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		TArray<class UShapeComponent*> Collisions;
};
