#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter_Base.generated.h"

class UCWeaponComponent;
class UCActionComponent;
class UCStatusComponent;
class UCStateComponent;
class UCFeetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACCharacter_Base*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumped);
UCLASS()
class CPORTFOLIO_API ACCharacter_Base : public ACharacter
{
	GENERATED_BODY()
public:
	ACCharacter_Base();

public:
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode) override;
	virtual void OnJumped_Implementation() override;
	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;
	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;
	virtual void Landed(const FHitResult& Hit) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UPROPERTY(EditDefaultsOnly)
		FVector LaunchZ_InAir;
	
protected:
	UPROPERTY(VisibleDefaultsOnly)
		UCWeaponComponent* WeaponComponent;
	
	UPROPERTY(VisibleDefaultsOnly)
		UCActionComponent* ActionComponent;
	
	UPROPERTY(VisibleDefaultsOnly)
		UCStatusComponent* StatusComponent;
	
	UPROPERTY(VisibleDefaultsOnly)
		UCStateComponent* StateComponent;
	
	UPROPERTY(VisibleDefaultsOnly)
		UCFeetComponent* FeetComponent;
	
public:
	FOnJumped OnJumped;
	

};

