#include "CProjectileLauncherComponent.h"

#include "Actions/CAction_Shot.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/KismetMathLibrary.h"


UCProjectileLauncherComponent::UCProjectileLauncherComponent() : ShotType(EShotType::Projectile), Range(1200.0f), ProjectileSpreadRatio(0.0f), RotationFactor(ProjectileSpreadRatio / 360.0f)
{
}

FVector const& UCProjectileLauncherComponent::GetEndVector(FVector const& StartVector, FVector& DirectionVector)
{
	DirectionVector = (UKismetMathLibrary::RandomRotator() * RotationFactor).RotateVector(DirectionVector);
	switch (ShotType)
	{
		case EShotType::LineTrace:
		{
			return ShotByLineTrace(StartVector, DirectionVector);
		}
		case EShotType::Projectile:
		{
			return ShotByProjectile(StartVector, DirectionVector);
		}
		default:
		{
			return FVector::ZeroVector;
		}
	}
}

FVector const& UCProjectileLauncherComponent::ShotByLineTrace(FVector const& StartVector, FVector const& DirectionVector)
{
	FHitResult Result;
	
	UWorld *World = GetWorld();
	FVector EndVector = StartVector + DirectionVector * Range;
	bool bHit = World->LineTraceSingleByObjectType(Result, StartVector, EndVector, CollisionObjectQueryParams, CollisionQueryParams);
	

	//라인트레이스에 성공하면 데미지 계산
	if(bHit)
	{
		EndVector = Result.ImpactPoint;
	}
	return EndVector;

	
	/*FColor color = bHit? FColor::Red : FColor::Green;
	DrawDebugLine(World, StartVector, EndVector, color, false, 10);
	*/

	/*//데미지 계산식 = Damage * (사거리 - 맞은 지점) / 사거리
	//멀리서 맞을 수록 정비례하게 데미지가 감소
	const float Damage = HitData.Damage * (Range - Result.Distance) / Range;

	//같은 액터가 여러발을 맞아도 데미지만 증가
	if(InActorsAndDamage.Contains(Result.Actor.Get()))
	{
		InActorsAndDamage[Result.Actor.Get()] += Damage;
	}
	//맞은 적 없는 액터는 새로 추가
	else
	{
		InActorsAndDamage.Add(Result.Actor.Get(), Damage);
	}*/
}

FVector const& UCProjectileLauncherComponent::ShotByProjectile(FVector const& StartVector, FVector const& DirectionVector) const
{
	return StartVector + DirectionVector * Range;
}

