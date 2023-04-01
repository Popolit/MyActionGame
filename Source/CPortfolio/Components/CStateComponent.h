#pragma once

#include "CoreMinimal.h"
#include "CoreEnums.h"
#include "Components/ActorComponent.h"
#include "Interfaces/CI_EventListener.h"
#include "CStateComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FStateTypeChanged, EStateType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAerialConditionChanged, bool);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCStateComponent : public UActorComponent, public ICI_EventListener
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
		FORCEINLINE bool IsSubActionMode() { return Type == EStateType::SubAction; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsHitMode() { return Type == EStateType::Hit; }
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
		void SetSubActionMode();
	UFUNCTION(BlueprintCallable)
		void SetActionMode();
	UFUNCTION(BlueprintCallable)
		void SetHitMode();
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
	FOnToggleEventTrigger OnToggleEventTrigger;
	FOnEventTrigger OnAirborneEventTrigger;
	FOnEventTrigger OnLandedEventTrigger;
	EStateType Type;
	bool bIsInAir;
};
