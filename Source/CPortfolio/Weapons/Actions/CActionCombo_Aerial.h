#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CActionCombo.h"
#include "CActionCombo_Aerial.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCActionCombo_Aerial : public UCActionCombo
{
	GENERATED_BODY()

public:
	UCActionCombo_Aerial();
	virtual void BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages) override;	

public:
	virtual void Pressed_Implementation() override;
public:
	virtual void BeginCombo() override;

	
protected:
	UFUNCTION()
		void OnAerialConditionChanged(bool IsInAir);

protected:
	bool bEnableAction;
};
