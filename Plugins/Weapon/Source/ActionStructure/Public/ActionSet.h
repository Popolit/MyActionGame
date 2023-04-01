#pragma once
#include "CoreMinimal.h"
#include "Action.h"
#include "ActionSet.generated.h"

class FKeyInputInterface;
UCLASS()
class ACTIONSTRUCTURE_API UActionSet : public UObject
{
	GENERATED_BODY()
	friend class UActionAsset;
public:
	UActionSet();
	
public:
	FORCEINLINE TArray<UAction*> GetActions() const { return Actions; }
	FORCEINLINE TArray<UAction*> GetActionsInAir() const { return ActionsInAir; }

public:
	template<typename T>
	void SetAllDelegations(T* InObject, void (T::*InFunction)(UAction*));
	void UnsetAllDelegations();
	
private:

private:
	UPROPERTY()
		TArray<UAction*> Actions_HasTrigger;
	
	UPROPERTY()
		TArray<UAction*> Actions;

	UPROPERTY()
		TArray<UAction*> ActionsInAir;
};

template <typename T>
void UActionSet::SetAllDelegations(T* InObject, void(T::*InFunction)(UAction*))
{
	for(UAction* Action : Actions)
	{
		if(Action != nullptr)
		{
			Action->OnActionBegin.BindUObject<T>(InObject, InFunction);
		}
	}

	for(UAction* Action : ActionsInAir)
	{
		if(Action != nullptr)
		{
			Action->OnActionBegin.BindUObject<T>(InObject, InFunction);
		}
	}
	
	for(UAction* Action : Actions_HasTrigger)
	{
		if(Action != nullptr)
		{
			Action->OnActionBegin.BindUObject<T>(InObject, InFunction);
		}
	}
}
