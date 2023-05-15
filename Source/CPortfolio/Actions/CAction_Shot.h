#pragma once

#include "CoreMinimal.h"
#include "IKeyInput.h"
#include "BaseClasses/CAction_Base.h"
#include "CAction_Shot.generated.h"

class UCWeaponComponent;
class UCProjectileLauncherComponent;
class UCStateComponent;
class ACProjectile;

/* Ranged Weapon Shot Action */
UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Shot : public UCAction_Base, public IIKeyInput
{
	GENERATED_BODY()
	
public:
	UCAction_Shot();
	
	virtual void BeginPlay() override;
public:
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;
	virtual void BeginDestroy() override;
protected:
	virtual FVector GetProjectileStartVector();
	virtual FVector SetEndVector(FVector const& InStartVector) const;
	virtual void SetProjectileLocationAndRotation();
	void HitProcess(FVector const& StartVector, FVector & EndVector,  TMap<AActor*, float>& InActorsAndDamage);

protected:
	UPROPERTY(EditDefaultsOnly)
		EShotType ShotType;
	
	//발사될 투사체 갯수
	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		uint8 ProjectilesCount;

	//투사체의 오브젝트 풀 갯수
	//ex) Projectile 갯수 = ProectilesCount * ProjectilePoolCount
	//오브젝트 풀 갯수가 적으면 투사체의 활용이 끝나기 전에 다시 발사될 수 있음
	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		uint8 ProjectilePoolCount;
	
	//사거리, 0 = 무한
	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		float Range;

	//탄 퍼짐 정도, 0~90도
	UPROPERTY(EditDefaultsOnly, Category="Projectiles", meta=(ClampMin=0, ClampMax=90))
		float ProjectileSpreadRatio;

	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		TSubclassOf<ACProjectile> ProjectileClass;

	//에디터에서 추가 시, OwnerCharacter를 제외하고 추가
	UPROPERTY(EditDefaultsOnly, Category="HitData")
		TArray<AActor*> ActorsToIgnore;

protected:
	UCStateComponent* StateComponent;
	UCProjectileLauncherComponent* ProjectileComponent;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	TArray<TArray<ACProjectile*>> Projectiles;
	uint8 ProjectileIndex;	//0 <= ProjectileIndex < ProjectilePoolCount
};
