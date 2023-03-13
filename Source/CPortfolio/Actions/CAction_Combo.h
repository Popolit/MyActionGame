#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "IKeyTrigger.h"
#include "CI_Action_Collision.h"
#include "CAction_Combo.generated.h"

class UCStateComponent;

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Combo : public UAction, public IIKeyTrigger//, public ICI_Action_Collision
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
public:
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;

private:
	virtual void BeginCombo();
	FORCEINLINE void SetComboEnable(bool const& IsComboEnable) { bComboEnable = IsComboEnable;}

private:
	UPROPERTY()
		UCStateComponent* StateComponent;
protected:
	UPROPERTY(EditDefaultsOnly)
		uint8 ComboMax;

private:
	uint8 ComboIndex;
	bool bComboEnable;
	bool bInputExist;
};
