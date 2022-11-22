#pragma once

#include "CoreMinimal.h"

class WEAPON_API SWeaponCheckBoxes	: public TSharedFromThis<SWeaponCheckBoxes>
{
public:
	void Add(FString InName, TSharedPtr<IPropertyHandle> InHandle);
	void Complete_Adding();

	void SetUtilities(TSharedPtr<class IPropertyUtilities> InUtilities);
	//SWidget은 위젯의 최상위 클래스
	TSharedRef<class SWidget> Draw();

private:
	TSharedRef<SWidget> DrawCheckBox(int32 InIndex);
	//void DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder InChildBuilder);

public:
	//void DrawProperties(TSharedRef<IPropertyHandle> InPropertyHandle);
	
private:
	bool bLocked;
	TSharedPtr<IPropertyUtilities> Utilities;

private:
	//내부적으로만 사용할 구조체
	struct FInternalData
	{
		bool bChecked;
		FString Name;
		TSharedPtr<IPropertyHandle> Handle;

		FInternalData() {}
		FInternalData(FString InName, TSharedPtr<IPropertyHandle> InHandle)
		{
			bChecked = false;
			Name = InName;
			Handle = InHandle;
		}
	};

	TArray<FInternalData> InternalDatas;
};
