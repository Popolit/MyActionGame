#include "CGameModeBase.h"
#include "CHelpers.h"

ACGameModeBase::ACGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Characters/Player/BP_CPlayer.BP_CPlayer_C'");
}