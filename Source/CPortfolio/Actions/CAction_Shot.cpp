#include "CAction_Shot.h"
#include "CHelpers.h"

#include "ActionFunctions.h"

#include "Weapon.h"
#include "WeaponAttachment.h"
#include "Characters/CCharacter_Base.h"
#include "Components/CProjectileLauncherComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Effects/CProjectile.h"
#include "Kismet/KismetMathLibrary.h"

UCAction_Shot::UCAction_Shot() : UCAction_Base(), ProjectilesCount(1),
                                 ProjectilePoolCount(1), Range(1200.0f), ProjectileSpreadRatio(100.0f), CollisionQueryParams(FCollisionQueryParams(NAME_None, false)), ProjectileIndex(0)
{
	//Pawn과 WorldStatic만 Hit함
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	//Projectiles Object Pool 초기화
	Projectiles = TArray<TArray<ACProjectile*>>(TArray<ACProjectile*>(), ProjectilePoolCount);

	//오브젝트 풀 내부 사이즈 예약
	for(TArray<ACProjectile*> ProjectilePool: Projectiles)
	{
		ProjectilePool.Reserve(ProjectilesCount);
	}
}

void UCAction_Shot::BeginPlay()
{
	Super::BeginPlay();

	//Divide By Zero 방지
	check(ProjectilePoolCount == 0);

	//기초 세팅
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);
	
	//Weaopn의 ProjectileComponent 가져오기
	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	check(WeaponComponent);

	UWeapon* Weapon = WeaponComponent->GetWeapon();
	check(Weapon);

	/*
	for(AWeaponAttachment* Attachment : Weapon->GetAttachments())
	{
		ProjectileComponent = CHelpers::GetComponent<UCProjectileLauncherComponent>(Attachment);
		if(ProjectileComponent != nullptr)
		{
			break;
		}
	}*/
	
	
	//LineTrace 콜리전 세팅
	CollisionQueryParams.AddIgnoredActor(OwnerCharacter);
	for(AActor * Actor : ActorsToIgnore)
	{
		CollisionQueryParams.AddIgnoredActor(Actor);
	}

	if(ProjectileClass == nullptr)
	{
		return;
	}
	
	//발사체를 갯수 * ProjectilePoolCount 만큼 미리 생성
	for(TArray<ACProjectile*> ProjectilePool: Projectiles)
	{
		for(ACProjectile* Projectile : ProjectilePool)
		{
			Projectile = OwnerCharacter->GetWorld()->SpawnActor<ACProjectile>(ProjectileClass);
			Projectile->SetActorHiddenInGame(true);
		}
	}
}

void UCAction_Shot::BeginAction()
{
	Super::BeginAction();

	//몽타주 재생
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

/* 발사체 소멸 작업 */
void UCAction_Shot::BeginDestroy()
{
	Super::BeginDestroy();

	for(TArray<ACProjectile*> ProjectilePool : Projectiles)
	{
		for(ACProjectile* Projectile : ProjectilePool)
		{
			Projectile->Destroy();
		}
	}
}

FVector UCAction_Shot::GetProjectileStartVector()
{
	//발사체의 시작 위치 벡터
	for(AWeaponAttachment* Attachment : Weapon->GetAttachments())
	{
		UCProjectileLauncherComponent* ProjectileComponent = CHelpers::GetComponent<UCProjectileLauncherComponent>(Attachment);
		if(ProjectileComponent != nullptr)
		{
			return ProjectileComponent->GetProjectileStartVector();
			break;
		}
	}

	return OwnerCharacter->GetActorLocation();
}

/* 라인 트레이스 및 히트 판정 */
void UCAction_Shot::HitProcess(FVector const& StartVector, FVector & EndVector, TMap<AActor*, float>& InActorsAndDamage)
{
	FHitResult Result;

	UWorld *World = OwnerCharacter->GetWorld();
	bool bHit = World->LineTraceSingleByObjectType(Result, StartVector, EndVector, CollisionObjectQueryParams, CollisionQueryParams);

	if(!bHit)
	{
		return;
	}

	//라인트레이스에 성공하면 데미지 계산
	EndVector = Result.ImpactPoint;
	/*FColor color = bHit? FColor::Red : FColor::Green;
	DrawDebugLine(World, StartVector, EndVector, color, false, 10);
	*/

	//데미지 계산식 = Damage * (사거리 - 맞은 지점) / 사거리
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
	}
}



