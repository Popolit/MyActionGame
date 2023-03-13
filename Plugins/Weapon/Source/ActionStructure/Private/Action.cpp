#include "Action.h"

UAction::UAction()
{
}

UAction::UAction(ACharacter* InOwner, TArray<FActionData> const& InActionDatas) : OwnerCharacter(InOwner), ActionDatas(InActionDatas)
{
}
