#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Replacement.h"
#include "Interfaces/CI_Collision.h"
#include "CAction_Combo_Branch.generated.h"

class UCStateComponent;

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Combo_Branch : public UCAction_Replacement, public ICI_Collision
{
	GENERATED_BODY()
public:
	UCAction_Combo_Branch();
public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;

	virtual void OnCollision(AActor* InAttackCauser, AActor* InTargetActor) override;
	
public:
	void BeginCombo();
	void EnableCombo(bool InIsEnableCombo);
	
private:
	UPROPERTY(EditDefaultsOnly)
		TArray<FHitData> HitDatas;
	
private:
	UCStateComponent* StateComponent;
	uint8 ComboMaxIndex;
	uint8 ComboIndex;
	bool bComboEnable;
	bool bInputExist;
};
