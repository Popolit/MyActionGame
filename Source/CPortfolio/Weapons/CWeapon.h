#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"


UCLASS()
class CPORTFOLIO_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();
protected:
	UPROPERTY(EditDefaultsOnly, Category="Equip")
		FName HolsterSocketName;
	UPROPERTY(EditDefaultsOnly, Category="Equip")
		FName RightHandSocketName;
	UPROPERTY(EditDefaultsOnly, Category="Equip")
		FName LeftHandSocketName;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;
		
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	class ACCharacter_Base* Owner;

};
