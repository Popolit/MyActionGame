#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "CTargetType.generated.h"


//  ******************************
//      Target Type
//  ******************************

//어빌리티의 타겟
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class CPORTFOLIO_API UCTargetType : public UObject
{
	GENERATED_BODY()

public:
	UCTargetType();
	UFUNCTION(BlueprintNativeEvent)
		void GetTargets(class ACCharacter_Base* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};


//  ******************************
//      Target Type UseOwner
//  ******************************
//Owner가 필요한 타켓
UCLASS(NotBlueprintable)
class CPORTFOLIO_API UCTargetType_UseOwner : public UCTargetType
{
	GENERATED_BODY()
public:
	UCTargetType_UseOwner();

public:
	virtual void GetTargets_Implementation(ACCharacter_Base* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};

//  ******************************
//      Target Type UseEventData
//  ******************************

UCLASS(NotBlueprintable)
class CPORTFOLIO_API UCTargetType_UseEventData : public UCTargetType
{
	GENERATED_BODY()
public:
	UCTargetType_UseEventData();

public:
	virtual void GetTargets_Implementation(ACCharacter_Base* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};
