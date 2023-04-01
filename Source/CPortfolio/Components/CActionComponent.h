#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionStructure.h"
#include "CActionComponent.generated.h"

class ACCharacter_Base;
class UCActionData;
class UActionSet;
class UAction;
class UCAction_Base;
class UWeapon;
class ICI_EventHandler;
class ICI_ToggleEventHandler;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCActionComponent();
	virtual void BeginPlay() override;
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	void BindActionEvent(FName const& InEventName, ICI_EventHandler* InEventHandler);
	void BindActionEvent(FName const& InEventName, ICI_ToggleEventHandler* InEventHandler);
	
	void OnWeaponChanged(UWeapon* PrevWeapon, UWeapon* NewWeapon);
	void OnActionBegin(UAction* InAction);
	void OnActionEvent(FName const& InEventName);
	void OnActionEvent(FName const& InEventName, bool const& IsEventOn);
	
	void OnAttachmentBeginOverlap(AActor* InAttackCauser, AActor* InTargetActor);
	void OnAttachmentOffCollision();

public:
	void KeyPressed(EActionType const& InActionInput) const;
	void KeyReleased(EActionType const& InActionInput) const;
	//void EndAction(EActionType const& InActionInput, bool IsInAir);
	
private:
	ACCharacter_Base* OwnerCharacter;
	TMap<FName, UCAction_Base*> ActionEvents;
	TMap<FName, UCAction_Base*> ActionToggleEvents;
	TArray<AActor*> HitActors;
	UActionSet* ActionSet;
	UAction* CurrAction;
};


