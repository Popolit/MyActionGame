#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Dash, Evade, Equip, Guard, Zoom, Action, Hitted, Dead, Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateTypeChanged, EStateType, NewStateType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAerialConditionChanged, bool, IsInAir);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCStateComponent();
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsDashMode() { return Type == EStateType::Dash; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsEvadeMode() { return Type == EStateType::Evade; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsGuardMode() { return Type == EStateType::Guard; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsZoomMode() { return Type == EStateType::Zoom; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsInAir() { return bIsInAir; }

public:
	UFUNCTION(BlueprintCallable)
		void SetIdleMode();
	UFUNCTION(BlueprintCallable)
		void SetDashMode();
	UFUNCTION(BlueprintCallable)
		void SetEvadeMode();
	UFUNCTION(BlueprintCallable)
		void SetEquipMode();
	UFUNCTION(BlueprintCallable)
		void SetGuardMode();
	UFUNCTION(BlueprintCallable)
		void SetZoomMode();
	UFUNCTION(BlueprintCallable)
		void SetActionMode();
	UFUNCTION(BlueprintCallable)
		void SetHittedMode();
	UFUNCTION(BlueprintCallable)
		void SetDeadMode();
	UFUNCTION(BlueprintCallable)
		void SetIsInAir(bool const& InAirCondition);	//True = IsInAir
	
	
private:
	void ChangeType(EStateType InType);

public:
	FStateTypeChanged OnStateTypeChanged;
	FOnAerialConditionChanged OnAerialConditionChanged;

private:
	EStateType Type;
	bool bIsInAir;
};
