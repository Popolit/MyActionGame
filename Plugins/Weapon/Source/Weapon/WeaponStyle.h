#pragma once

#include "CoreMinimal.h"

//웨폰 플러그인의 스타일 정의
class WEAPON_API FWeaponStyle
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

	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	FSlateIcon ToolBar_Icon;
};
