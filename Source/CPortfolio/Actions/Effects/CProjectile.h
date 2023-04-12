#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

class UArrowComponent;
class UProjectileMovementComponent;

UCLASS(BlueprintType)
class CPORTFOLIO_API ACProjectile : public AActor
{
	GENERATED_BODY()
public:	
	ACProjectile();

	virtual void Tick(float DeltaSeconds) override;
public:
	virtual void Shoot();
	void Shoot(FVector const& InEndVector);

	void StopProjectile() const;
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
		UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
		UArrowComponent* Arrow;
	
private:
	FVector EndLocation;
};