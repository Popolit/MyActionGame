#pragma once

#include "CoreMinimal.h"
#include "CAN_SpawnActor.generated.h"

UCLASS()
class CPORTFOLIO_API UCAN_SpawnActor : public UAnimNotify
{
	GENERATED_BODY()
	
	UCAN_SpawnActor();
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	UPROPERTY(EditInstanceOnly)
		TSubclassOf<AActor> ActorClass;
	
private:
	const FString NotifyName;
};
