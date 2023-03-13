#pragma once

#include "CoreMinimal.h"
#include "CAction_Combo.h"
#include "CI_Action_CanBranch.h"
#include "CAction_Combo_Branch.generated.h"


UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Combo_Branch : public UCAction_Combo, public ICI_Action_CanBranch
{
	GENERATED_BODY()
public:
	virtual void SetBranchAction(UAction* InBranchAction) override;
private:
	UPROPERTY(EditDefaultsOnly)
		UAction* BranchAction;
};
