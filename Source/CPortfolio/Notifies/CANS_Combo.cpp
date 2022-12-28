#include "CANS_Combo.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionCombo.h"


FString UCANS_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCANS_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCActionComponent* actionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComponent);
	
	UCActionCombo* action = Cast<UCActionCombo>(actionComponent->GetAction(EActionType::Action));
	CheckNull(action);
	action->SetComboEnable(true);
}

void UCANS_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCActionComponent* actionComponent = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComponent);
	
	UCActionCombo* action = Cast<UCActionCombo>(actionComponent->GetAction(EActionType::Action));
	CheckNull(action);
	action->SetComboEnable(false);
}
