#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionStructure.h"
#include "CActionAsset.generated.h"

UCLASS()
class CPORTFOLIO_API UCActionAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	friend class UCActionComponent;
	UCActionAsset();

	void BeginPlay(class ACCharacter_Base* InOwner, class UCActionData** OutActionData);
private:
	UPROPERTY(EditAnywhere, Category="Actions")
		TArray<FActionData> ActionDatas;
};
