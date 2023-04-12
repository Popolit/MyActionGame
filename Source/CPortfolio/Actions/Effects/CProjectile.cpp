#include "CProjectile.h"
#include "CHelpers.h"
#include "Components/ArrowComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACProjectile::ACProjectile()
{
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");
	CHelpers::CreateActorComponent<UArrowComponent>(this, &Arrow, "Arrow");
	
	Projectile->InitialSpeed = 10000.0f;
	Projectile->MaxSpeed = 10000.0f;
	Projectile->ProjectileGravityScale = 0;

	PrimaryActorTick.bCanEverTick = true;
}

//목표를 지나면 Hidden
void ACProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(UKismetMathLibrary::Dot_VectorVector(GetActorForwardVector(), (EndLocation - GetActorLocation())) < 0)
	{
		SetActorHiddenInGame(true);
		Projectile->SetComponentTickEnabled(false);
		SetActorTickEnabled(false);
	}
}

void ACProjectile::Shoot()
{
	SetActorTickEnabled(true);
	Projectile->SetComponentTickEnabled(true);
	Projectile->Velocity = Arrow->GetForwardVector() * Projectile->InitialSpeed;
	EndLocation = GetActorLocation() + Arrow->GetForwardVector() * 40000.0f;
}


void ACProjectile::Shoot(FVector const& InEndLocation)
{
	SetActorTickEnabled(true);
	Projectile->SetComponentTickEnabled(true);
	Projectile->Velocity = Arrow->GetForwardVector() * Projectile->InitialSpeed;
	EndLocation = InEndLocation;
}

void ACProjectile::StopProjectile() const
{
	Projectile->Velocity = FVector::ZeroVector;
}


