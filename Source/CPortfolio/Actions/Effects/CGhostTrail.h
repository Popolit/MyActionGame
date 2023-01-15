#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGhostTrail.generated.h"

UCLASS()
class CPORTFOLIO_API ACGhostTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	ACGhostTrail();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Capture")
	float LifeSpan = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Capture")
	float StartDelay = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Capture")
	float Interval = 0.25f;
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	class UMaterialInstanceConstant* MaterialInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FLinearColor Color = FLinearColor(1, 1, 1, 1);
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	float Exp = 1;


private:
	UPROPERTY(VisibleDefaultsOnly)
	class UPoseableMeshComponent* Mesh;
	
private:
	class ACharacter* OwnerCharacter;
	class UMaterialInstanceDynamic* Material;
	
	FTimerHandle TimerHandle;
};
