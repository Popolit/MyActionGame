/*
#pragma once

#include "CoreMinimal.h"
#include "ActionStructure.h"
#include "Interfaces/CI_Action_HasCollision.h"

class UCStateComponent;

class CPORTFOLIO_API FActionCanComboObject : public ICI_Action_HasCollision
{
public:
	FActionCanComboObject();
	
protected:
	void SetComboDelegation();
	void BeginCombo();
	void EnableCombo(bool InIsEnableCombo);
	
public:
	virtual void OnCollision(AActor* InAttackCauser,AActor* InTargetActor) override;

private:
	TArray<FHitData> HitDatas;
	UCStateComponent* StateComponent;
	uint8 ComboMaxIndex;
	uint8 ComboIndex;
	bool bComboEnable;
	bool bInputExist;
};
*/
