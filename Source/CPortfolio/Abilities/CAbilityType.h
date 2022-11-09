#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "CAbilityType.generated.h"

//  ******************************
//      Effect Container
//  ******************************
//이펙트, 태그, 타겟팅을 정의한 구조체
USTRUCT(BlueprintType)
struct FCGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FCGameplayEffectContainer();

public:
	//타겟의 타입
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
		TSubclassOf<class UCTargetType> TargetType;
	
	//타겟에게 적용할 이펙트들
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
		TArray<TSubclassOf<class UGameplayEffect>> TargetGameplayEffectClasses;
};


//  ******************************
//      Effect Container Spec
//  ******************************
USTRUCT(BlueprintType)
struct FCGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	FCGameplayEffectContainerSpec();

public:
	bool HasValidEffects() const;
	bool HasValidTargets() const;
	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);

public:
	//타겟 데이터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
		FGameplayAbilityTargetDataHandle TargetData;

	//타겟에게 적용될 이펙트들
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
		TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

};
