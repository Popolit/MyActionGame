#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "CAbilityType.generated.h"

//  ******************************
//      Effect Container
//  ******************************
//����Ʈ, �±�, Ÿ������ ������ ����ü
USTRUCT(BlueprintType)
struct FCGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FCGameplayEffectContainer();

public:
	//Ÿ���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
		TSubclassOf<class UCTargetType> TargetType;
	
	//Ÿ�ٿ��� ������ ����Ʈ��
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
	//Ÿ�� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
		FGameplayAbilityTargetDataHandle TargetData;

	//Ÿ�ٿ��� ����� ����Ʈ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
		TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

};
