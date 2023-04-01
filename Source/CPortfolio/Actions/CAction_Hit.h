#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Base.h"
#include "Tickable.h"
#include "Interfaces/CI_ToggleEventHandler.h"
#include "CAction_Hit.generated.h"

class UCAction_Hit_InAir;
class UCStateComponent;
class UCStatusComponent;

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Hit : public UCAction_Base, public FTickableGameObject, public ICI_ToggleEventHandler
{
	GENERATED_BODY()
	
public:
	UCAction_Hit();
	
public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;

public:
	virtual void HandleEvent(bool IsEventOn) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetWorld() const override;

private:
	void OnDamaged(float const& InAmount, float const& InStaggerTime);

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UCAction_Hit_InAir> Action_Hit_InAirClass;
	UPROPERTY()
		UCAction_Hit_InAir* Action_Hit_InAir;
private:
	const FName EventName;
	float StaggerTime;
	int32 MontageIndex;
	UCStateComponent* StateComponent;
	UCStatusComponent* StatusComponent;
};


