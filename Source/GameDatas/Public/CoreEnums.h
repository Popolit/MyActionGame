#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed, Sword, Shotgun, Max,
};

UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk, Run, Sprint, Max,
};

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Dash, Evade, Equip, SubAction, Action, Hit, Dead, Max,
};