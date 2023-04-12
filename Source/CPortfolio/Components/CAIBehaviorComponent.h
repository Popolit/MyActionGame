#pragma once

#include "CoreMinimal.h"
#include "CoreEnums.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ActorComponent.h"
#include "CAIBehaviorComponent.generated.h"

class UCActionComponent;
class UBehaviorTree;
class ACCharacter_Base;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAIBehaviorComponent();

	virtual void BeginPlay() override;
public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	FORCEINLINE UBlackboardComponent* GetBlackboard() const { return Blackboard; }
	FORCEINLINE void SetBlackboard(UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }
	FORCEINLINE ACCharacter_Base* GetTarget() const;
	
public:
	UFUNCTION(BlueprintPure)
		bool IsIdleMode() const;

	UFUNCTION(BlueprintPure)
		bool IsChaseMode() const;

	UFUNCTION(BlueprintPure)
		bool IsRetreatMode() const;

	UFUNCTION(BlueprintPure)
		bool IsEvadeMode() const;

	UFUNCTION(BlueprintPure)
		bool IsSubActionMode() const;

	UFUNCTION(BlueprintPure)
		bool IsActionMode() const;

	UFUNCTION(BlueprintPure)
		bool IsHitMode() const;

	UFUNCTION(BlueprintPure)
		bool IsDeadMode() const;

public:
	void ChangeBehaviorType(EBehaviorType const& InBehaviorType);
	
	void SetIdleMode();
	void SetChaseMode();
	void SetReatreatMode();
	void SetEvadeMode();
	void SetSubActionMode();
	void SetActionMode();
	void SetHitMode();
	void SetDeadMode();

private:
	void OnStateTypeChanged(EStateType InStateType);
	

	
private:
	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditDefaultsOnly)
		FName TargetKey;

	UPROPERTY(EditDefaultsOnly)
		FName BehaviorKey;
	
private:
	UBlackboardComponent* Blackboard;
	UCActionComponent* ActionComponent;
};

