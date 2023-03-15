#include "ActionEditorStyle.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FActionEditorStyle> FActionEditorStyle::Instance = nullptr;

//SingleTone
TSharedRef<FActionEditorStyle> FActionEditorStyle::Get()
{
	if(!Instance.IsValid())
	{
		Instance = MakeShareable(new FActionEditorStyle(), Destroyer{});
	}
	
	return Instance.ToSharedRef();
}

void FActionEditorStyle::Shutdown()
{
	if(!Instance.IsValid())
	{
		return;
	}
	Instance.Reset();
}

const FSlateIcon& FActionEditorStyle::GetToolBarIcon() const
{
	return ToolBarIcon;
}

FActionEditorStyle::FActionEditorStyle() : StyleSetName("ActionEditorStyle"), StyleSet(MakeShareable(new FSlateStyleSet(StyleSetName)))
{
	//Root 경로 설정
	FString Path = IPluginManager::Get().FindPlugin("Weapon")->GetBaseDir();
	Path  = Path / "Resources";
	StyleSet->SetContentRoot(Path);

	RegisterIcon("ToolBarIcon", Path / "Icon_Action.png", FVector2D(48, 48), ToolBarIcon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

FActionEditorStyle::~FActionEditorStyle()
{
	if(!StyleSet.IsValid())
	{
		return;
	}
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
	StyleSet.Reset();
}

void FActionEditorStyle::RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* Brush = new FSlateImageBrush(InPath, InIconSize);
	FString Name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(Name), Brush);

	OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(Name));
}