#include "WeaponEditorStyle.h"

#include "Textures/SlateIcon.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FWeaponEditorStyle> FWeaponEditorStyle::Instance = nullptr;

//SingleTon 패턴
TSharedRef<FWeaponEditorStyle> FWeaponEditorStyle::Get()
{
	if (!Instance.IsValid())
	{
		Instance = MakeShareable(new FWeaponEditorStyle(), Destroyer{});
	}
	
	return Instance.ToSharedRef();
}

//인스턴스가 있으면 소멸
void FWeaponEditorStyle::Shutdown()
{
	if(!Instance.IsValid())
	{
		return;
	}
	Instance.Reset();
}

const FSlateIcon& FWeaponEditorStyle::GetToolBarIcon() const
{
	return ToolBarIcon;
}

//Weapon Editor 생성자
FWeaponEditorStyle::FWeaponEditorStyle() : StyleSetName("WeaponEditorStyle"), StyleSet(MakeShareable(new FSlateStyleSet(StyleSetName)))
{
	//Root 경로 설정
	FString Path = IPluginManager::Get().FindPlugin("Weapon")->GetBaseDir();
	Path  = Path / "Resources";
	StyleSet->SetContentRoot(Path);

	RegisterIcon("ToolBarIcon", Path / "Icon_Weapon.png", FVector2D(48, 48), ToolBarIcon);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

//소멸자
FWeaponEditorStyle::~FWeaponEditorStyle()
{
	if(!StyleSet.IsValid())
	{
		return;
	}
	
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
	StyleSet.Reset();
}

//Weapon Editor 아이콘 등록
void FWeaponEditorStyle::RegisterIcon(const FString& InName, const FString& InPath, const FVector2D& InIconSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* Brush = new FSlateImageBrush(InPath, InIconSize);
	FString Name = StyleSetName.ToString() + "." + InName;
	StyleSet->Set(FName(Name), Brush);

	OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(Name));
}
