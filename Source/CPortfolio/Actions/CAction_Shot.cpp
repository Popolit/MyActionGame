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
	//Pawn과 WorldStatic만 Hit함
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
}

void UCAction_Shot::BeginPlay()
{
	Super::BeginPlay();

	//기초 세팅
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);

	CameraComponent = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	check(WeaponComponent);

	//LineTrace 콜리전 세팅
	CollisionQueryParams.AddIgnoredActor(OwnerCharacter);
	for(AActor * Actor : ActorsToIgnore)
	{
		CollisionQueryParams.AddIgnoredActor(Actor);
	}

	//발사체 오브젝트 풀 세팅
	Projectiles[0].Reserve(ProjectilesCount);
	Projectiles[1].Reserve(ProjectilesCount);
	Projectiles[2].Reserve(ProjectilesCount);
	
	//발사체를 갯수 * 3 만큼 미리 생성
	for(uint8 P_Index = 0; P_Index < 3; P_Index++)
	{
		for(uint8 U = 0; U < ProjectilesCount; U++)
		{
			ACProjectile* Projectile = OwnerCharacter->GetWorld()->SpawnActor<ACProjectile>(ProjectileClass);
			Projectile->SetActorHiddenInGame(true);
			Projectiles[P_Index].Push(Projectile);
		}
	}
}

/* 발사 */
void UCAction_Shot::BeginAction()
{
	Super::BeginAction();

	//발사체 오브젝트 풀 Index + 1
	ProjectileIndex = (ProjectileIndex + 1) % 3;
	
	AWeaponAttachment* Weapon = WeaponComponent->GetWeapon()->GetAttachments()[0];
	check(Weapon);
	
	UArrowComponent* Arrow = CHelpers::GetComponent<UArrowComponent>(Weapon);
	check(Arrow);

	//발사체의 시작 지점과 끝 지점 세팅
	const FVector BulletStartVector = Arrow->GetComponentLocation();
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
		for(uint8 U = 0; U < ProjectilesCount; U++)
		{
			EndVectors.Push(MakeBulletTrajectory(StandardVector));
			HitProcess(StartVector, EndVectors[U], HitActorsAndDamage);

			if(ProjectileClass != nullptr)
			{
				Projectiles[ProjectileIndex][U]->SetActorLocation(BulletStartVector);
				Projectiles[ProjectileIndex][U]->SetActorRotation((EndVectors[U] - BulletStartVector).Rotation());
				Projectiles[ProjectileIndex][U]->SetActorHiddenInGame(false);
				Projectiles[ProjectileIndex][U]->Shoot(EndVectors[U]);
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

	for(uint8 P_Index = 0; P_Index < 3; P_Index++)
	{
		for(ACProjectile* Bullet : Projectiles[P_Index])
		{
			Bullet->Destroy();
		}
	}
}

/* LineTrace의 끝 지점을 만드는 작업, 탄 퍼짐 정도에 따라 랜덤으로 변경됨 */
FVector UCAction_Shot::MakeBulletTrajectory(FVector const& InStandardVector) const
{
	return FVector(InStandardVector.X + UKismetMathLibrary::RandomFloatInRange(ProjectileSpreadRatio * -1.0f, ProjectileSpreadRatio),
		InStandardVector.Y + UKismetMathLibrary::RandomFloatInRange(ProjectileSpreadRatio * -1.0f, ProjectileSpreadRatio),
		InStandardVector.Z + UKismetMathLibrary::RandomFloatInRange(ProjectileSpreadRatio * -1.0f, ProjectileSpreadRatio));
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



