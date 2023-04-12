#include "CAction_Shot.h"
#include "CHelpers.h"

#include "ActionFunctions.h"

#include "Weapon.h"
#include "WeaponAttachment.h"
#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Effects/CProjectile.h"
#include "Kismet/KismetMathLibrary.h"

UCAction_Shot::UCAction_Shot() : UCAction_Base(),
                                 ProjectilesCount(15), Range(1200.0f), ProjectileSpreadRatio(100.0f), CollisionQueryParams(FCollisionQueryParams(NAME_None, false)), ProjectileIndex(0)
{
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
}

void UCAction_Shot::BeginPlay()
{
	Super::BeginPlay();
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);

	CameraComponent = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	check(WeaponComponent);

	CollisionQueryParams.AddIgnoredActor(OwnerCharacter);
	for(AActor * Actor : ActorsToIgnore)
	{
		CollisionQueryParams.AddIgnoredActor(Actor);
	}

	Projectiles.Reserve(ProjectilesCount * 3);
	//오브젝트 풀처럼 미리 생성해둔 Bullet 객체 재활용
	for(uint8 U = 0; U < ProjectilesCount * 3; U++)
	{
		ACProjectile* Projectile = OwnerCharacter->GetWorld()->SpawnActor<ACProjectile>(ProjectileClass);
		Projectile->SetActorHiddenInGame(true);
		Projectiles.Push(Projectile);
	}
}

void UCAction_Shot::BeginAction()
{
	Super::BeginAction();

	ProjectileIndex = (ProjectileIndex + 1) % 3;
	AWeaponAttachment* Weapon = WeaponComponent->GetWeapon()->GetAttachments()[0];
	check(Weapon);
	
	UArrowComponent* Arrow = CHelpers::GetComponent<UArrowComponent>(Weapon);
	check(Arrow);

	
	const FVector BulletStartVector = Arrow->GetComponentLocation();
	TArray<FVector> EndVectors;
	TMap<AActor*, float> HitActorsAndDamage;
	FHitData ProcessedHitData = HitData;	//실제로 전달될 히트데이터
	EndVectors.Reserve(ProjectilesCount);

	//Player : Make Bullets Trajectory
	if(CameraComponent != nullptr)
	{
		const FVector StartVector = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 300.0f;
		const FVector StandardVector = StartVector + CameraComponent->GetForwardVector() * Range;
		
		for(uint8 U = ProjectilesCount * ProjectileIndex; U < ProjectilesCount * (ProjectileIndex + 1); U++)
		{
			EndVectors.Push(MakeBulletTrajectory(StandardVector));
			HitProcess(StartVector, EndVectors[U], HitActorsAndDamage);

			if(ProjectileClass != nullptr)
			{
				Projectiles[U]->SetActorLocation(BulletStartVector);
				Projectiles[U]->SetActorRotation((EndVectors[U] - BulletStartVector).Rotation());
				Projectiles[U]->SetActorHiddenInGame(false);
				Projectiles[U]->Shoot(EndVectors[U]);
			}
		}

		for(TTuple<AActor*, float> Element : HitActorsAndDamage)
		{
			ACCharacter_Base* TargetCharacter = Cast<ACCharacter_Base>(Element.Key);
			ProcessedHitData.Damage = Element.Value;
			if(TargetCharacter != nullptr)
			{
				ActionFunctions::PlayHitEffect(ProcessedHitData, OwnerCharacter, TargetCharacter);
				ActionFunctions::SendDamage(&ProcessedHitData, OwnerCharacter, OwnerCharacter, TargetCharacter);
			}
			else
			{
				//총알 구멍 텍스쳐
			}
		}
	}
	
	if(ActionDatas.IsValidIndex(0))
	{
		ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
	}
}

void UCAction_Shot::EndAction()
{
	Super::EndAction();

	ActionFunctions::EndAction(OwnerCharacter);
}

void UCAction_Shot::KeyPressed()
{
	if(StateComponent->IsSubActionMode() && bActionEnded)
	{
		BeginAction();
	}
}

void UCAction_Shot::KeyReleased()
{
}

void UCAction_Shot::BeginDestroy()
{
	Super::BeginDestroy();

	for(ACProjectile* Bullet : Projectiles)
	{
		Bullet->Destroy();
	}
}

FVector UCAction_Shot::MakeBulletTrajectory(FVector const& InStandardVector) const
{
	return FVector(InStandardVector.X + UKismetMathLibrary::RandomFloatInRange(ProjectileSpreadRatio * -1.0f, ProjectileSpreadRatio),
		InStandardVector.Y + UKismetMathLibrary::RandomFloatInRange(ProjectileSpreadRatio * -1.0f, ProjectileSpreadRatio),
		InStandardVector.Z + UKismetMathLibrary::RandomFloatInRange(ProjectileSpreadRatio * -1.0f, ProjectileSpreadRatio));
}

void UCAction_Shot::HitProcess(FVector const& StartVector, FVector & EndVector, TMap<AActor*, float>& InActorsAndDamage)
{
	FHitResult Result;

	UWorld *World = OwnerCharacter->GetWorld();
	bool bHit = World->LineTraceSingleByObjectType(Result, StartVector, EndVector, CollisionObjectQueryParams, CollisionQueryParams);

	if(!bHit)
	{
		return;
	}
	EndVector = Result.ImpactPoint;
	/*FColor color = bHit? FColor::Red : FColor::Green;
	DrawDebugLine(World, StartVector, EndVector, color, false, 10);
	*/
	const float Damage = HitData.Damage * (Range - Result.Distance) / Range;
	
	if(InActorsAndDamage.Contains(Result.Actor.Get()))
	{
		InActorsAndDamage[Result.Actor.Get()] += Damage;
	}
	else
	{
		InActorsAndDamage.Add(Result.Actor.Get(), Damage);
	}
}



