#include "ActionStructure.h"



FHitData::FHitData() : Damage(0), Launch(100), LaunchZ(0), StaggerTime(0), StopTime(0), Effect(),
				EffectLocation(FVector::ZeroVector), EffectScale(FVector::OneVector), SoundCue()
{
}

FActionTrigger::FActionTrigger() : FActionTrigger(false,  EActionType::None)
{
}

FActionTrigger::FActionTrigger(bool InIsInAir, EActionType InActionType)
			: IsInAir(InIsInAir), ActionType(InActionType)
{
}

FActionTrigger::FActionTrigger(const FActionTrigger& Other)
			: FActionTrigger(Other.IsInAir, Other.ActionType)
{
}

FActionData::FActionData() : Montage(), PlayRatio(1.0f), bCanMove(true), bFixedCamera(false), Effect(), EffectLocation(FVector::ZeroVector),
			EffectScale(FVector::OneVector)
{
}

IMPLEMENT_MODULE(FDefaultModuleImpl, ActionStructure)