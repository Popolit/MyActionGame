#pragma once

#include "CoreMinimal.h"
#include "CProjectileLauncherComponent.generated.h"

class UArrowComponent;
class ACProjectile;


/* Types Define How to Shot Projectile */
UENUM(BlueprintType)
enum class EShotType : uint8
{
	LineTrace,				//Use LineTrace
	Projectile,				//Use ProjectileMovementComponent
};


/**
 * Component for Projectiles
 * This Component Confirm How to Shot Projectile
 * This Component Only return EndVector(Location)
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCProjectileLauncherComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCProjectileLauncherComponent();

public:
	FVector const& GetEndVector(FVector const& StartVector, FVector& DirectionVector);

private:
	FVector const& ShotByLineTrace(FVector const& StartVector, FVector const& DirectionVector);
	FVector const& ShotByProjectile(FVector const& StartVector, FVector const& DirectionVector) const;
	
private:	
	UPROPERTY(EditDefaultsOnly)
		EShotType ShotType;
	
	//사거리, 0 = 무한
	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		float Range;

	//탄 퍼짐 정도, 0~90도
	UPROPERTY(EditDefaultsOnly, Category="Projectiles", meta=(ClampMin=0, ClampMax=90))
		float ProjectileSpreadRatio;

private:
	const float RotationFactor;
};


