#pragma once

#include "CoreMinimal.h"
#include "CAction.h"
#include "CGuard.generated.h"

UCLASS(Blueprintable)
class CPORTFOLIO_API UCGuard : public UCAction
{
	GENERATED_BODY()

public:
	UCGuard();
	virtual void BeginPlay(ACCharacter_Base* InOwner, const TArray<FActionMontage>& InActionMontages) override;	
	
public:
	virtual void Pressed_Implementation() override;
	virtual void Released_Implementation() override;

	virtual void EndAction_Implementation() override;

private:
	bool bCanParry;
};
