#include "CEquipData.h"

#include "Animation/AnimMontage.h"

FCEquipData::FCEquipData()
    : Type(EquipType::Equip)
    , Montage(nullptr)
    , Playratio(1.0f)
    , bUseControlRotation(false)
    , bCanMove(false)
{

}