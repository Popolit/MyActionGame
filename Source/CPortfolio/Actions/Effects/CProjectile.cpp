#include "CProjectile.h"
#include "CHelpers.h"
#include "Components/CProjectileLauncherComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACProjectile::ACProjectile()
{
	//Projectile Movement Component 셋팅
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");
	
	Projectile->InitialSpeed = 10000.0f;
	Projectile->MaxSpeed = 10000.0f;
	Projectile->ProjectileGravityScale = 0;

	CHelpers::CreateActorComponent<UCProjectileLauncherComponent>(this, &ProjectileLauncherComponent, "ProjectileLauncher");

	PrimaryActorTick.bCanEverTick = true;
}

void ACProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Dot Product를 이용해 목표 지점을 지났는 지 확인
	//목표를 지났다면 Tick을 끄고 액터를 숨김
	if(UKismetMathLibrary::Dot_VectorVector(GetActorForwardVector(), (EndLocation - GetActorLocation())) < 0)
	{
		SetActorHiddenInGame(true);
		Projectile->SetComponentTickEnabled(false);
		SetActorTickEnabled(false);
	}
}

/**
 * Projectile을 목표 지점으로 발사
 * @param InEndLocation 목표 지점
 */
void ACProjectile::Shoot(FVector const& InEndLocation)
{
	ProjectileLauncherComponent->GetEndVector();
	SetActorTickEnabled(true);
	Projectile->SetComponentTickEnabled(true);
	Projectile->Velocity = GetActorForwardVector() * Projectile->InitialSpeed;
	EndLocation = InEndLocation;
}

/* Projectile을 멈춤 */
void ACProjectile::StopProjectile() const
{
	Projectile->Velocity = FVector::ZeroVector;
}


