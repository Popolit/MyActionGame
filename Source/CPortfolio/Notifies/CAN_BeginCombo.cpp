#include "CAN_BeginCombo.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionCombo.h"

FString UCAN_BeginCombo::GetNotifyName_Implementation() const
{
	return "BeginCombo";
}

void UCAN_BeginCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCActionComponent* actionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComponent);
	
	UCActionCombo* action = Cast<UCActionCombo>(actionComponent->GetAction(EActionType::Action));
	CheckNull(action);
	action->BeginCombo();
}