#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

class ACCharacter_Base;
class UCActionData;
class UCStateComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCActionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

/*public:
	void KeyPressed(EActionType const& InActionInput);
	void KeyReleased(EActionType const& InActionInput);

public:
	void StateChanged(EStateType NewStateType);*/
	
private:
	UPROPERTY()
		ACCharacter_Base* OwnerCharacter;
	/*
	UPROPERTY()
		UCACtionData* DefaultActions;
	UPROPERTY()
		UCStateComponent* StateComponent;
		*/

/*
private:
	TMap<EActionType, UCAction_Base*> Actions_TriggeredByKey;
	TMap<EStateType, UCAction_Base*> Actions_TriggeredByState;
	TArray<ICI_Tickable*> Actions_Tickable;*/
};



/*
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
	class UCStatusComponent* StatusComponent;

//  **********************
//      Action & Trigger
//  **********************
	
public:
	UFUNCTION(BlueprintCallable)
		UCAction_Base* GetAction(EActionType const & InActionInput);
	UFUNCTION()
		void SetStateTrigger(EStateType InStateType);
	UFUNCTION()
		void SetAerialTrigger(bool IsInAir);
	UFUNCTION()
		void SetActionTrigger(EActionType InActionType);
	UFUNCTION()
		void OnWeaponChanged(enum EWeaponType PrevWeaponType, enum EWeaponType NewWeaponType);

private:
	bool SetAction();

public:
	void EndAction(EActionType const & InActionInput);

private:
	UPROPERTY()
		UCAction_Base* Actions[(uint8)EActionType::None + 1];
	UPROPERTY()
		UCActionData* ActionData;
		
private:
	FActionTrigger Trigger;
	UCAction_Base** RecentAction;
	uint8 const ActionMax = (uint8)EActionType::None + 1;
	
public:
	FOnActionChanged OnActionChanged;

//  *********************
//      Overlap Event
//  *********************
private:
	void OnAttachmentBeginOverlap(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter);
	void OnAttachmentEndOverlap(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter);
	void OnAttachmentOffCollision();
	
private:
	TArray<ACCharacter_Base*> Arr_Hitted;
	
//  *********************
//      Inputs
//  *********************
public:
	void ExecuteActionInput(EActionType InActionInput, bool InPressed);

public:
	FOnActionInput OnActionInput;

public:
	void KeyPressed(EActionType const & InActionInput);
	void KeyReleased(EActionType const & InActionInput);
};
*/


