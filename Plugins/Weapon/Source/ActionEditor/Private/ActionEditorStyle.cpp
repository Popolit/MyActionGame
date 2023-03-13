#include "ActionEditorStyle.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

const FName FActionEditorStyle::StyleSetName = "ActionStyle";
TSharedPtr<FActionEditorStyle> FActionEditorStyle::Instance = nullptr;

//SingleTone
TSharedRef<FActionEditorStyle> FActionEditorStyle::Get()
{
	if(!Instance.IsValid())
	{
		Instance = MakeShareable(new FActionEditorStyle());
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

FActionEditorStyle::FActionEditorStyle() : StyleSet(MakeShareable(new FSlateStyleSet(StyleSetName)))
{
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
