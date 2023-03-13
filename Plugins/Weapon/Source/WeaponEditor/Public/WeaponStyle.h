#pragma once

#include "CoreMinimal.h"

class FSlateStyleSet;

class WEAPONEDITOR_API FWeaponStyle
{
public:
	static TSharedRef<FWeaponStyle> Get();
	static void Shutdown();

private:
	static TSharedPtr<FWeaponStyle> Instance;

public:
	FWeaponStyle();
	~FWeaponStyle();

private:
	void RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon);

private:
	static const FName StyleSetName;
	TSharedPtr<FSlateStyleSet> StyleSet;

public:
	FSlateIcon ToolBar_Icon;
};
