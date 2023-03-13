#include "CAN_EndAction.h"
#include "CHelpers.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CActionComponent.h"

UCAN_EndAction::UCAN_EndAction() : NotifyName("EndAction")
{
}

FString UCAN_EndAction::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComponent);

	//actionComponent->EndAction(ActionType);
}
