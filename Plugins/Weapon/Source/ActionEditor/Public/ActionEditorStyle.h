#pragma once
#include "CoreMinimal.h"

class FSlateStyleSet;

class ACTIONEDITOR_API FActionEditorStyle
{
public:
	static TSharedRef<FActionEditorStyle> Get();
	static void Shutdown();

public:
	FActionEditorStyle();
	~FActionEditorStyle();

	// Disable copy/move constructor and operator=.
	FActionEditorStyle(const FActionEditorStyle&) = delete;
	FActionEditorStyle(FActionEditorStyle&&) = delete;
	FActionEditorStyle& operator=(const FActionEditorStyle&) = delete;
	FActionEditorStyle& operator=(FActionEditorStyle&&) = delete;

private:
	struct Destroyer
	{
		void operator()(FActionEditorStyle* Ptr){ delete Ptr;}
	};
	friend Destroyer;

private:
	static const FName StyleSetName;
	static TSharedPtr<FActionEditorStyle> Instance;
	TSharedPtr<FSlateStyleSet> StyleSet;
};
