#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.h"
#include "CAction_Evade.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Evade : public UCAction
{
	GENERATED_BODY()
public:
	virtual void BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages) override;
	virtual void Tick(float InDeltaTime) override;
	virtual void Pressed_Implementation() override;

	virtual void EndAction_Implementation() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		uint8 MaxActionCount = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float CoolTime = 2.0f;
	
private:
	uint8 ActionCountLeft;
	float CoolTimeLeft = 0.0f;
};
