#pragma once

#include "CoreMinimal.h"
#include "CAction_Shot.h"
#include "CAction_Shot_Gun.generated.h"

class UCWeaponComponent;
class UCStateComponent;
class ACProjectile;

/* Ranged Weapon Shot Action With LineTrace */
UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Shot_Gun : public UCAction_Shot
{
	GENERATED_BODY()
	
public:
	UCAction_Shot_Gun();
	virtual void BeginPlay() override;

public:
	virtual void BeginAction() override;

protected:
	virtual void Shot();
	virtual void GetStartVectorAndRotation(FVector& InStartVector, FRotator& InProjectileRotation) override;
	virtual FVector SetEndVector(FVector const& InStartVector) const override;
	virtual void MakeBulletTrajectory(FVector const& InStandardVector);
	void HitProcess(FVector const& StartVector, FVector & EndVector,  TMap<AActor*, float>& InActorsAndDamage);
	
	
protected:
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	TArray<TArray<ACProjectile*>> Projectiles;	//ProjectilesCount * 3개 저장
	uint8 ProjectileIndex;	//Range = 0, 1, 2
};
