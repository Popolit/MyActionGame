#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Base.h"
#include "IKeyInput.h"
#include "CAction_Zoom.generated.h"

class UCStatusComponent;
class UCStateComponent;

USTRUCT(BlueprintType)
struct FAimData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float TargetArmLength = 100;

	UPROPERTY(EditAnywhere)
		FVector SocketOffset = FVector(0, 50, 50);

	UPROPERTY(EditAnywhere)
		bool bEnableCameraLag = false;
};


UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Zoom : public UCAction_Base, public IIKeyInput, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UCAction_Zoom();
	
public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;
	virtual void KeyReleased() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetWorld() const override;

private:
	UFUNCTION()
		void OnAiming(float InAmount) const;
	
private:
	UPROPERTY(EditDefaultsOnly)
		UCurveFloat* Curve;

	UPROPERTY(EditDefaultsOnly)
		FAimData AimData;
	
private:
	UCStateComponent* StateComponent;
	UCStatusComponent* StatusComponent;
	USpringArmComponent* SpringArm;
	UCameraComponent* Camera;
	
	FAimData OriginData;
	FTimeline Timeline;
	
};
