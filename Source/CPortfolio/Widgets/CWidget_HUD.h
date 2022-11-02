#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_HUD.generated.h"

UCLASS()
class CPORTFOLIO_API UCWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
	void UpdateHP(const float& InCurrHP, const float& InMaxHP);
	void UpdateMP(const float& CurrMP, const float& MaxMP);

//º¯¼ö
private:	
	class UProgressBar* HealthBar;
	class UProgressBar* ManaBar;
	uint8 FrameCount = 0;
};
