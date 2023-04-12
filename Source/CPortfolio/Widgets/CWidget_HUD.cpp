#include "Widgets/CWidget_HUD.h"

#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"

void UCWidget_HUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(WidgetTree->RootWidget);

	TArray<UWidget*> widgets = CanvasPanel->GetAllChildren();
	for (UWidget* Widget : widgets)
	{
		UProgressBar* ProgressBar = Cast<UProgressBar>(Widget);
		if (!ProgressBar)
		{
			continue;
		}
		if (ProgressBar->GetFName() == "HealthBar")
		{
			HealthBar = ProgressBar;
		}
		else if (ProgressBar->GetFName() == "ManaBar")
		{
			ManaBar = ProgressBar;
		}
	}
}


void UCWidget_HUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FrameCount++;
}

void UCWidget_HUD::UpdateHP(const float& InCurrHP, const float& InMaxHP)
{
	HealthBar->SetPercent(InCurrHP / InMaxHP);
}

void UCWidget_HUD::UpdateMP(const float& InCurrMP, const float& InMaxMP)
{
	ManaBar->SetPercent(InCurrMP / InMaxMP);
}
