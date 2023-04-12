#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/CAction_Replacement.h"
#include "Interfaces/CI_Collision.h"
#include "CAction_DashAttack.generated.h"

class UCStateComponent;
UCLASS(Blueprintable, HideDropDown)
class CPORTFOLIO_API UCAction_DashAttack : public UCAction_Replacement, public ICI_Collision
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;

	virtual void OnCollision(AActor* InAttackCauser, AActor* InTargetActor) override;

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<FHitData> HitDatas;
private:
	UCStateComponent* StateComponent;
};
