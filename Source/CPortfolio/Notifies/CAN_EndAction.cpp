#include "CAN_EndAction.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CActionComponent.h"
#include "Actions/CAction.h"

FString UCAN_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAN_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCActionComponent* actionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComponent);

	actionComponent->EndAction(ActionType);
}
