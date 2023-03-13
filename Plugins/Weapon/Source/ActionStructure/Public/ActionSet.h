#pragma once
#include "CoreMinimal.h"
#include "ActionStructure.h"
#include "ActionSet.generated.h"

class UAction;
class IITickable;
UCLASS()
class ACTIONSTRUCTURE_API UActionSet : public UObject
{
	GENERATED_BODY()
	friend class UActionAsset;
private:
	UPROPERTY()
		UAction* Actions[EActionType::None];
	UPROPERTY()
		UAction* ActionsInAir[EActionType::None];
	UPROPERTY()
		TArray<TScriptInterface<IITickable>> Actions_Tickable;
};