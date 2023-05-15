#include "CAction_Shot_Gun.h"

#include "CHelpers.h"
#include "Weapon.h"
#include "WeaponAttachment.h"
#include "Characters/Player/CPlayer.h"
#include "Components/CProjectileLauncherComponent.h"
#include "Components/CWeaponComponent.h"

UCAction_Shot_Gun::UCAction_Shot_Gun()
{
}

void UCAction_Shot_Gun::BeginPlay()
{
	Super::BeginPlay();

	/*CollisionQueryParams.AddIgnoredActor(OwnerCharacter);
	for(AActor * Actor : ActorsToIgnore)
	{
		CollisionQueryParams.AddIgnoredActor(Actor);
	}*/
}

void UCAction_Shot_Gun::BeginAction()
{
	Super::BeginAction();
	UWeapon* Weapon = WeaponComponent->GetWeapon();
	check(Weapon);

	FVector const ProjectileStartVector = GetProjectileStartVector();
	FVector LineTraceStartVector = ProjectileStartVector;
	FVector LineTraceEndVector;
	
	//플레이어일 경우, ViewpPoint에서 LineTrace의 끝지점을 생성
	if(OwnerCharacter->StaticClass() == ACPlayer::StaticClass())
	{
		FRotator LineTraceRotator;
		OwnerCharacter->GetController()->GetPlayerViewPoint(LineTraceStartVector, LineTraceRotator);

		LineTraceEndVector = LineTraceStartVector + (LineTraceRotator.Vector() * Range);
	}
	
	
	

	//발사체의 시작 지점과 끝 지점 세팅
	TArray<FVector> EndVectors;
	TMap<AActor*, float> HitActorsAndDamage;
	FHitData ProcessedHitData = HitData;	//실제로 전달될 히트데이터
	EndVectors.Reserve(ProjectilesCount);

	//카메라 컴포넌트가 있음 : 플레이어
	//플레이어는 카메라의 중심(에임 점)을 기준으로 LineTrace
	if(CameraComponent != nullptr)
	{
		const FVector StartVector = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * 300.0f;
		const FVector StandardVector = StartVector + CameraComponent->GetForwardVector() * Range;

		//발사체의 갯수만큼 발사 작업
		for(ACProjectile* Projectile : Projectiles[ProjectileIndex])
		{
			EndVectors.Push(MakeProjectileTrajectory(StandardVector));
			HitProcess(StartVector, EndVectors[U], HitActorsAndDamage);

			if(ProjectileClass != nullptr)
			{
				Projectile->SetActorLocation(BulletStartVector);
				Projectile->SetActorRotation((EndVectors[U] - BulletStartVector).Rotation());
				Projectile->SetActorHiddenInGame(false);
				Projectile->Shoot(EndVectors[U]);
			}
		}

		//히트한 유효 액터들에게 데미지 전달
		for(TTuple<AActor*, float> Element : HitActorsAndDamage)
		{
			ACCharacter_Base* TargetCharacter = Cast<ACCharacter_Base>(Element.Key);
			ProcessedHitData.Damage = Element.Value;

			//맞은 액터가 캐릭터면 데미지 전달
			if(TargetCharacter != nullptr)
			{
				ActionFunctions::PlayHitEffect(ProcessedHitData, OwnerCharacter, TargetCharacter);
				ActionFunctions::SendDamage(&ProcessedHitData, OwnerCharacter, OwnerCharacter, TargetCharacter);
			}
			//맞은 액터가 땅, 벽 등 WorldStatic이면 상흔을 남김
			else
			{
				//작업 예정 : 총알 구멍 텍스쳐 구현
			}
		}
	}
}

void UCAction_Shot_Gun::Shot()
{
	//발사체 오브젝트 풀 Index + 1
	ProjectileIndex = (ProjectileIndex + 1) % ProjectilePoolCount;

	for(ACProjectile* Projectile : Projectiles[ProjectileIndex])
	{
		MakeBulletTrajectory();
		
	}
}

void UCAction_Shot_Gun::GetStartVectorAndRotation(FVector& InStartVector, FRotator& InProjectileRotation)
{
	if(OwnerCharacter == nullptr)
	{
		return;
	}
	
	OwnerCharacter->GetController()->GetPlayerViewPoint(InStartVector, InProjectileRotation);
}


FVector UCAction_Shot_Gun::SetEndVector(FVector const& InForwardVector) const
{
	
}


