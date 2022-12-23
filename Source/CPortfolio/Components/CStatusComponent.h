#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk, Run, Sprint, Max,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeedType::Max] = { 200, 400, 600 };

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100;

public:
	UFUNCTION(BlueprintCallable)
		void Move() { bCanMove = true; }
	UFUNCTION(BlueprintCallable)
		void Stop() { bCanMove = false; }
	UFUNCTION(BlueprintCallable)
		void Action() { bCanAction = true; }
	UFUNCTION(BlueprintCallable)
		void StopAction() { bCanAction = false; }
	
public:
	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ESpeedType::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ESpeedType::Sprint]; }

	FORCEINLINE bool CanMove() { return bCanMove; }
	FORCEINLINE bool CanAction() { return bCanAction; }


	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

	FORCEINLINE bool GetFixedCamera() { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }

	FORCEINLINE bool GetTopView() { return bTopView; }
	FORCEINLINE void EnableTopView() { bTopView = true; }
	FORCEINLINE void DisableTopView() { bTopView = false; }

public:	
	UCStatusComponent();

	void Damage(float InAmount);

	void EnableControlRotation();
	void DisableControlRotation();

protected:
	virtual void BeginPlay() override;

private:
	class ACharacter* OwnerCharacter;

	bool bCanMove = true;
	bool bCanAction = true;
	float Health;

	bool bFixedCamera;
	bool bTopView;
};
