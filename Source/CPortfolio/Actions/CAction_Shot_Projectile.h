#pragma once

#include "CoreMinimal.h"
#include "CAction_Shot.h"
#include "Interfaces/CI_Collision.h"
#include "Interfaces/CI_EventHandler.h"
#include "CAction_Shot_Projectile.generated.h"

UCLASS(Blueprintable, HideDropdown)
class CPORTFOLIO_API UCAction_Shot_Projectile : public UCAction_Shot, public ICI_EventHandler, public ICI_Collision
{
	GENERATED_BODY()
public:
	UCAction_Shot_Projectile();

	virtual void BeginPlay() override;
public:
	virtual void BeginAction() override;
	virtual void EndAction() override;
	virtual void KeyPressed() override;

	virtual void OnCollision(AActor* InAttackCauser, AActor* InTargetActor) override;
	virtual void HandleEvent() override;

private:
	UPROPERTY(EditDefaultsOnly)
		FName ProjectileHolsterSocket;
	
	UPROPERTY(EditDefaultsOnly)
		FName ProjectileSocket;

	UPROPERTY(EditDefaultsOnly)
		FName EventName;
};
