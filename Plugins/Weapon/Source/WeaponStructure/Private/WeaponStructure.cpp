#include "WeaponStructure.h"


FEquipData::FEquipData() : Montage(nullptr), PlayRatio(1.0f), bCanMove(true), bUseControlRotation(true)
{
}

FUnEquipData::FUnEquipData() : Montage(nullptr), PlayRatio(1.0f)
{
}

IMPLEMENT_MODULE(FDefaultModuleImpl, WeaponStructure)