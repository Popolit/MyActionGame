#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

class UArrowComponent;
class UProjectileMovementComponent;

/* Actor has projectile Class */
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

	//Projectile이 날아갈 방향
	UPROPERTY(VisibleDefaultsOnly)
		UArrowComponent* Arrow;
	
private:
	FVector EndLocation;
};