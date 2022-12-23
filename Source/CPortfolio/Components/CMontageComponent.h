#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CStateComponent.h"
#include "Engine/DataTable.h"
#include "CMontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EStateType Type;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRatio = 1;
};

///////////////////////////////////////////////////////////////////////////////

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPORTFOLIO_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()
};

