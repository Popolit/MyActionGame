#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"


class UCProjectileLauncherComponent;
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
	void Shoot(FVector const& InEndVector);
	void StopProjectile() const;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UProjectileMovementComponent* Projectile;

	UPROPERTY(EditDefaultsOnly)
		UCProjectileLauncherComponent* ProjectileLauncherComponent;
	
private:
	FVector EndLocation;
};