#pragma once
#include "CoreMinimal.h"

class FSlateStyleSet;

/* Set Action Editor Icon */
class ACTIONEDITOR_API FActionEditorStyle
{
public:
	static TSharedRef<FActionEditorStyle> Get();
	static void Shutdown();
	const FSlateIcon& GetToolBarIcon() const;

private:
	FActionEditorStyle();
	~FActionEditorStyle();

	//이동, 복사 생성자 제거
	FActionEditorStyle(const FActionEditorStyle&) = delete;
	FActionEditorStyle(FActionEditorStyle&&) = delete;
	FActionEditorStyle& operator=(const FActionEditorStyle&) = delete;
	FActionEditorStyle& operator=(FActionEditorStyle&&) = delete;

	void RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon);

private:
	struct Destroyer
	{
		void operator()(FActionEditorStyle const* Ptr) const { delete Ptr;}
	};
	friend Destroyer;



private:
	FName  const StyleSetName;
	static TSharedPtr<FActionEditorStyle> Instance;
	TSharedPtr<FSlateStyleSet> StyleSet;
	FSlateIcon ToolBarIcon;
};
