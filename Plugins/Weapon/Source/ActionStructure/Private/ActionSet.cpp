#include "ActionSet.h"


#include "ActionStructure.h"

UActionSet::UActionSet()
{
	Actions.SetNum((uint8)EActionType::None);
	ActionsInAir.SetNum((uint8)EActionType::None);
}



void UActionSet::UnsetAllDelegations()
{
	for(UAction* Action : Actions)
	{
		if(Action != nullptr)
		{
			Action->OnActionBegin.Unbind();
		}
	}

	for(UAction* Action : ActionsInAir)
	{
		if(Action != nullptr)
		{
			Action->OnActionBegin.Unbind();
		}
	}

	for(UAction* Action : Actions_HasTrigger)
	{
		if(Action != nullptr)
		{
			Action->OnActionBegin.Unbind();
		}
	}
}
