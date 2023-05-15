#pragma once

#include "CoreMinimal.h"
#include "CAction_Shot.h"
#include "Interfaces/CI_Collision.h"
#include "Interfaces/CI_EventHandler.h"
#include "CAction_Shot_Projectile.generated.h"

/* Ranged Weapon Shot Action With Projectile Collision */
//임시로 공용이 아닌 Archery 전용 클래스로 사용
UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Shot_Projectile : public UCAction_Shot, public ICI_EventHandler, public ICI_Collision
{
	GENERATED_BODY()
public:
	UCAction_Shot_Projectile();

	virtual void BeginPlay() override;
public:
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;

	virtual void OnCollision(AActor* InAttackCauser, AActor* InTargetActor) override;
	virtual void HandleEvent() override;

private:
	//Projectile (Arrow)의 소지 소켓
	UPROPERTY(EditDefaultsOnly)
		FName ProjectileHolsterSocket;

	//Projectile의 손 소켓
	UPROPERTY(EditDefaultsOnly)
		FName ProjectileSocket;

	//활 시위를 당길 때 등 이벤트 이름
	UPROPERTY(EditDefaultsOnly)
		FName EventName;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* AnimationAsset;

private:
	USkeletalMeshComponent* AttachmentMeshComponent;
};
