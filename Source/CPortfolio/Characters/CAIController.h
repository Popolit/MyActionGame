#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class UCAIBehaviorComponent;
class ACCharacter_Base;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class CPORTFOLIO_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	

private:
	UPROPERTY(VisibleDefaultsOnly)
		UAIPerceptionComponent* Perception;

private:
	ACCharacter_Base* OwnerCharacter;
	UCAIBehaviorComponent* BehaviorComponent;
	UAISenseConfig_Sight* Sight;
};
