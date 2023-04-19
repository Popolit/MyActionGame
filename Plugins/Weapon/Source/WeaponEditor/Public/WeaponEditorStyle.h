#pragma once

#include "CoreMinimal.h"

class FSlateStyleSet;

/* Register WeaponEditor Icon, Singleton */
class WEAPONEDITOR_API FWeaponEditorStyle
{
public:
	static TSharedRef<FWeaponEditorStyle> Get();
	static void Shutdown();
	const FSlateIcon& GetToolBarIcon() const;

private:
	FWeaponEditorStyle();
	~FWeaponEditorStyle();

	//이동, 복사 생성자 제거
	FWeaponEditorStyle(const FWeaponEditorStyle&) = delete;
	FWeaponEditorStyle(FWeaponEditorStyle&&) = delete;
	FWeaponEditorStyle& operator=(const FWeaponEditorStyle&) = delete;
	FWeaponEditorStyle& operator=(FWeaponEditorStyle&&) = delete;

	void RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon);

private:
	struct Destroyer
	{
		void operator()(FWeaponEditorStyle const* Ptr) const { delete Ptr;}
	};
	friend Destroyer;



private:
	static TSharedPtr<FWeaponEditorStyle> Instance;
	FName const StyleSetName;
	TSharedPtr<FSlateStyleSet> StyleSet;
	FSlateIcon ToolBarIcon;
};
