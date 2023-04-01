#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Replacement.h"
#include "Interfaces/CI_Action_HasCollision.h"
#include "Interfaces/CI_EventHandler.h"
#include "CAction_UpperAttack.generated.h"

class UCStateComponent;

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_UpperAttack : public UCAction_Replacement, public ICI_EventHandler, public ICI_Action_HasCollision
{
	GENERATED_BODY()
public:
	UCAction_UpperAttack();
	
public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;

public:
	virtual void HandleEvent() override;
	virtual void OnCollision(AActor* InAttackCauser, AActor* InTargetActor) override;

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<FHitData> HitDatas;
private:
	UCStateComponent* StateComponent;
	bool bKeyPressed;
};
