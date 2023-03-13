#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionStructure.h"
#include "Action.generated.h"

//Action Class
UCLASS()
class ACTIONSTRUCTURE_API UAction : public UObject
{
	GENERATED_BODY()
public:
	UAction();
	UAction(ACharacter* InOwner, TArray<FActionData> const& InActionDatas);
public:
	//Need to Override
	virtual void BeginPlay() {}
	virtual void BeginAction() {}
	virtual void EndAction() {}
	
protected:
	UPROPERTY(EditDefaultsOnly)
		TArray<FActionData> ActionDatas;
protected:
	ACharacter* OwnerCharacter;
};


