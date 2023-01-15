#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAction.h"
#include "CAction_Hitted_Aerial.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCAction_Hitted_Aerial : public UCAction
{
	GENERATED_BODY()
public:
	virtual void BeginPlay(ACCharacter_Base* InOwner, TArray<FActionMontage> const& InActionMontages) override;
public:
	virtual void Pressed_Implementation() override;
	virtual void EndAction_Implementation() override;

public:
	UFUNCTION()
		void OnLanded(const FHitResult& Hit);

private:
	bool bHitted = false;
};
