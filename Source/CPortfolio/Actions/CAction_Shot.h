#pragma once

#include "CoreMinimal.h"
#include "IKeyInput.h"
#include "BaseClasses/CAction_Base.h"
#include "CAction_Shot.generated.h"

class UCWeaponComponent;
class UCStateComponent;
class ACProjectile;

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Shot : public UCAction_Base, public IIKeyInput
{
	GENERATED_BODY()
	
public:
	UCAction_Shot();
	
public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;
	virtual void BeginDestroy() override;

private:
	FVector MakeBulletTrajectory(FVector const& InStandardVector) const;
	void HitProcess(FVector const& StartVector, FVector & EndVector,  TMap<AActor*, float>& InActorsAndDamage);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		uint8 ProjectilesCount;

	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		float Range;

	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		float ProjectileSpreadRatio;

	UPROPERTY(EditDefaultsOnly, Category="Projectiles")
		TSubclassOf<ACProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="HitData")
		FHitData HitData;

	/*UPROPERTY(EditDefaultsOnly, Category="HitData")
		TArray<TEnumAsByte<EObjectTypeQuery>> HitObjects;*/

	//에디터에서 추가 시, OwnerCharacter를 제외하고 추가
	UPROPERTY(EditDefaultsOnly, Category="HitData")
		TArray<AActor*> ActorsToIgnore;
	
protected:
	UCStateComponent* StateComponent;
	UCameraComponent* CameraComponent;
	UCWeaponComponent* WeaponComponent;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	FCollisionQueryParams CollisionQueryParams;
	TArray<ACProjectile*> Projectiles;	//ProjectilesCount * 3개 저장
	uint8 ProjectileIndex;	//Range = 0, 1, 2
};
