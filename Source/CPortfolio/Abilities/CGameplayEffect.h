#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "CGameplayEffect.generated.h"

UCLASS()
class CPORTFOLIO_API UCGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Effects")
		FName EffectID;
};
