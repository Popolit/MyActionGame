#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.h"
#include "CI_Action_Tick.h"
#include "CAction_Evade.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Evade : public UCAction, public ICI_Action_Tick
{
	GENERATED_BODY()
public:
	virtual void BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages) override;
	virtual void Tick(float const& InDeltaTime) override;
	
	virtual void Pressed_Implementation() override;

	virtual void EndAction_Implementation() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		uint8 MaxActionCount = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float CoolTime = 0.5f;
	
protected:
	uint8 ActionCountLeft;
	float CoolTimeLeft = 0.0f;
};
