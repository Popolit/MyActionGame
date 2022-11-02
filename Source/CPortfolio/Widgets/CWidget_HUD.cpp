#include "Widgets/CWidget_HUD.h"
#include "Global.h"

#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanelSlot.h"



void UCWidget_HUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UCanvasPanel* panel = Cast<UCanvasPanel>(WidgetTree->RootWidget);

	TArray<UWidget*> widgets = panel->GetAllChildren();
	for (UWidget* widget : widgets)
	{
		UProgressBar* pb = Cast<UProgressBar>(widget);
		if (!pb)
			continue;
		if (pb->GetFName() == "HealthBar")
			HealthBar = pb;
		else if (pb->GetFName() == "ManaBar")
			ManaBar = pb;
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
	CLog::Print(InMaxHP);
}

void UCWidget_HUD::UpdateMP(const float& InCurrMP, const float& InMaxMP)
{
	ManaBar->SetPercent(InCurrMP / InMaxMP);
	CLog::Print(InMaxMP);
}
