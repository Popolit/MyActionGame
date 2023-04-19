#include "ActionSet.h"


#include "ActionStructure.h"

//Action의 갯수를 ActionType의 갯수만큼 초기화
UActionSet::UActionSet()
{
	Actions.SetNum((uint8)EActionType::None);
	ActionsInAir.SetNum((uint8)EActionType::None);
}


//모든 OnActionBegin의 델리게이션 해제
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
