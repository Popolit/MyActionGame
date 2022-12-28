#include "CActionAsset.h"

#include "CAction.h"
#include "CActionData.h"
#include "CI_Action_Tick.h"

UCActionAsset::UCActionAsset()
{
}

void UCActionAsset::BeginPlay(ACCharacter_Base* InOwner, UCActionData** OutActionData)
{
	*OutActionData = NewObject<UCActionData>();

	uint32 stateTypeMaxSize = (uint32)EStateType::Max;
	for(FActionData actionData : ActionDatas)
	{
		if(!actionData.ActionClass)
			continue;
		UCAction* newAction = NewObject<UCAction>(this, actionData.ActionClass);
		newAction->BeginPlay(InOwner, actionData.Montages);
		
		uint32 stateTypes = actionData.StateTypeFlags;
		
		for(uint32 u = 0; u < stateTypeMaxSize; u++)
		{
			//BitMask, 해당 StateType에 체크되어 있지 않으면 continue
			if((1 & (stateTypes >> u)) == 0)
				continue;
			FActionTrigger trigger = {(EStateType)u, actionData.IsInAir, actionData.ActionType};
			(*OutActionData)->Actions.Emplace(trigger, newAction);
		}

		//Tickable Action
		ICI_Action_Tick* tickableAction = Cast<ICI_Action_Tick>(newAction);
		if(tickableAction != nullptr)
			(*OutActionData)->TickableActions.Push(newAction);
	}
	
}
