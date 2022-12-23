#include "CWeapon.h"

#include "CAttachment.h"
#include "CEquipment.h"
#include "Global.h"
#include "Actions/CAction.h"

void UCWeapon::EndPlay(ACCharacter_Base* InOwner)
{
	for (ACAttachment* attachment : Attachments)
	{
		attachment->Destroy();
		attachment = nullptr;
	}

	if (!!Equipment)
	{
		Equipment->ConditionalBeginDestroy();
		Equipment = nullptr;
	}
}
