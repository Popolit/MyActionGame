#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CI_EventListener.h"
#include "CCharacter_Base.generated.h"

class UWeapon;
class UCWeaponComponent;
class UCActionComponent;
class UCStatusComponent;
class UCStateComponent;
class UCFeetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACCharacter_Base*, Character);


/* ��� ĳ������ ���� Ŭ���� */
UCLASS()
class CPORTFOLIO_API ACCharacter_Base : public ACharacter, public ICI_EventListener,  public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ACCharacter_Base();

	virtual void BeginPlay() override;

public:
	bool IsInAir();
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamId); }
	FORCEINLINE float GetAimPitch() const { return AimPitch; }
	FORCEINLINE float GetAimYaw() const { return AimYaw; }
	
private:
	void OnWeaponChanged(UWeapon* PrevWeapon, UWeapon* NewWeapon);

public:
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode) override;
	virtual void OnJumped_Implementation() override;
	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;
	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;
	virtual void Landed(const FHitResult& Hit) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	
protected:
	//�Ǿ� �ĺ� ID
	UPROPERTY(EditDefaultsOnly)
		uint8 TeamId;

	//���߿��� �ǰ� �� �ߴ� ����
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
	//���� ��
	FOnEventTrigger OnJumpEventTrigger;

private:
	float AimYaw;
	float AimPitch;
};

