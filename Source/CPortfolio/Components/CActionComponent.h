#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actions/CActionData.h"
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
	class UCStatusComponent* StatusComponent;

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
		void OnWeaponChanged(enum EWeaponType PrevWeaponType, enum EWeaponType NewWeaponType);

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
	void Pressed(EActionType const & InActionInput);
	void Released(EActionType const & InActionInput);
};


