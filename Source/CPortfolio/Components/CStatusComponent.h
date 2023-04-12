#pragma once

#include "CoreMinimal.h"
#include "CoreEnums.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDamaged, float const&, float const&)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCStatusComponent();
	
	virtual void BeginPlay() override;
	
public:
	FORCEINLINE void EnableMove() { bCanMove = true; }
	FORCEINLINE void DisableMove() { bCanMove = false; }
	FORCEINLINE void EnableAction() { bCanAction = true; }
	FORCEINLINE void DisableAction() { bCanAction = false; }
	FORCEINLINE void EnableDash() { bCanDash = true; }
	FORCEINLINE void DisableDash() { bCanDash = false; }
	
	FORCEINLINE float GetWalkSpeed() const { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() const { return Speed[(int32)ESpeedType::Run]; }

	FORCEINLINE bool CanMove() const { return bCanMove; }
	FORCEINLINE bool CanAction() const { return bCanAction; }
	FORCEINLINE bool CanDash() const { return bCanDash; }

	
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE bool GetFixedCamera() const { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }

public:
	void Damage(float const& InAmount, float const& InStaggerTime);

	void EnableControlRotation();
	void DisableControlRotation();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float Speed[(uint8)ESpeedType::Max];

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		float MaxHealth;


public:
	FOnDamaged OnDamaged;
	
private:
	ACharacter* OwnerCharacter;

	bool bCanMove;
	bool bCanAction;
	bool bCanDash;
	bool bFixedCamera;
	float Health;

};
