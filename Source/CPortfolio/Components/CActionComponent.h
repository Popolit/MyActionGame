#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/Actions/CActionData.h"
#include "CActionComponent.generated.h"

DECLARE_DELEGATE_TwoParams(FOnActionInput, EActionType, bool)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActionChanged, class UCAction*, class UCAction*)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

//  *********************
//      기본 세팅
//  *********************
public:	
	UCActionComponent();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	class ACCharacter_Base* OwnerCharacter;
	class UCWeaponComponent* WeaponComponent;

//  **********************
//      Action & Trigger
//  **********************
	
public:
	UFUNCTION(BlueprintCallable)
		UCAction* GetAction(EActionType const & InActionInput);
	UFUNCTION()
		void SetStateTrigger(EStateType InStateType);
	UFUNCTION()
		void SetAerialTrigger(bool IsInAir);
	UFUNCTION()
		void SetActionTrigger(EActionType InActionType);
	UFUNCTION()
		void SetActionData(enum EWeaponType PrevWeaponType, enum EWeaponType NewWeaponType);

private:
	bool SetAction();

public:
	void EndAction(EActionType const & InActionInput);

private:
	UPROPERTY()
		UCAction* Actions[(uint8)EActionType::None + 1];
	UPROPERTY()
		UCActionData* ActionData;
		
private:
	FActionTrigger Trigger;
	UCAction** RecentAction;
	uint8 const ActionMax = (uint8)EActionType::None + 1;
public:
	FOnActionChanged OnActionChanged;
	
//  *********************
//      Inputs
//  *********************
public:
	void ExecuteActionInput(EActionType InActionInput, bool InPressed);

public:
	FOnActionInput OnActionInput;

public:
	void Pressed(EActionType const & InActionInput);
	void Released(EActionType const & InActionInput);
};


