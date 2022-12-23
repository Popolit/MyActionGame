#include "CAN_EndAction.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CActionComponent.h"
#include "Weapons/Actions/CAction.h"

FString UCAN_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAN_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACCharacter_Base* character = Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(character);

	UCActionComponent* actionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComponent);

	actionComponent->EndAction(ActionType);
}
