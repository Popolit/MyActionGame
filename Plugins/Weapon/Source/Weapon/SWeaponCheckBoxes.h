#pragma once

#include "CoreMinimal.h"

class WEAPON_API SWeaponCheckBoxes	: public TSharedFromThis<SWeaponCheckBoxes>
{
public:
	void Add(FString InName, TSharedPtr<IPropertyHandle> InHandle);
	void Complete_Adding();

	void SetUtilities(TSharedPtr<class IPropertyUtilities> InUtilities);
	//SWidget�� ������ �ֻ��� Ŭ����
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
	//���������θ� ����� ����ü
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
