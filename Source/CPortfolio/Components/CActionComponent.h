#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionStructure.h"
#include "CActionComponent.generated.h"

class ACCharacter_Base;
class UCActionData;
class UActionSet;
class UAction;
class UWeapon;
class ICI_EventHandler;
class ICI_EventHandler_Toggle;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCActionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	void BindActionEvent(FName const& InEventName, ICI_EventHandler* InEventHandler);
	void BindActionEvent(FName const& InEventName, ICI_EventHandler_Toggle* InEventHandler);
	
	void OnWeaponChanged(UWeapon* PrevWeapon, UWeapon* NewWeapon);
	void OnActionBegin(UAction* InAction);
	void OnActionEvent(FName const& InEventName);
	void OnActionEvent(FName const& InEventName, bool const& IsEventOn);
	
public:
	void KeyPressed(EActionType const& InActionInput);
	void KeyReleased(EActionType const& InActionInput) const;
	void EndAction(EActionType const& InActionInput, bool IsInAir);
	
private:
	UPROPERTY()
		ACCharacter_Base* OwnerCharacter;
	
private:
	TMap<FName, UAction*> ActionEvents;
	TMap<FName, UAction*> ActionToggleEvents;
	UActionSet* ActionSet;
	UAction* CurrAction;
};


