#include "WeaponStyle.h"

#include "Textures/SlateIcon.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

const FName FWeaponStyle::StyleSetName = "WeaponStyle";

TSharedPtr<FWeaponStyle> FWeaponStyle::Instance = nullptr;

//SingleTone 패턴
TSharedRef<FWeaponStyle> FWeaponStyle::Get()
{
	if (!Instance.IsValid())
		Instance = MakeShareable(new FWeaponStyle());

	return Instance.ToSharedRef();
}

void FWeaponStyle::Shutdown()
{
	if(!Instance.IsValid())
		return;
	
	Instance.Reset();
}

FWeaponStyle::FWeaponStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));
	
	//Root 경로 설정
	FString path = IPluginManager::Get().FindPlugin("Weapon")->GetBaseDir();
	path  = path / "Resources";
	StyleSet->SetContentRoot(path);

	RegisterIcon("ToolBar_Icon", path / "Icon_Weapon.png", FVector2D(48, 48), ToolBar_Icon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

FWeaponStyle::~FWeaponStyle()
{
	if(!StyleSet.IsValid())
		return;

	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
	StyleSet.Reset();
}

void FWeaponStyle::RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath, InIconSize);
	FString name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(name), brush);

	OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(name));
}
