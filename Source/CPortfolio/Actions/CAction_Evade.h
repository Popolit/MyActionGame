#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "IKeyTrigger.h"
#include "ITickable.h"
#include "CAction_Evade.generated.h"

class UCStateComponent;

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Evade : public UAction, public IIKeyTrigger, public IITickable
{
	GENERATED_BODY()
public:
	UCAction_Evade();
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
public:
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;

public:
	virtual void Tick(float const& InDeltaTime) override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
		uint8 MaxActionCount;
	UPROPERTY(EditDefaultsOnly)
		float CoolTime;
protected:
	uint8 ActionCountLeft;
	float CoolTimeLeft;

private:
	UPROPERTY()
		UCStateComponent* StateComponent;
};
