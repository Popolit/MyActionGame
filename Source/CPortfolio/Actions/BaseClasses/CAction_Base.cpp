#include "CAction_Base.h"

#include "CHelpers.h"
#include "Notifies/CAN_EndAction.h"

void UCAction_Base::BeginPlay()
{
	Super::BeginPlay();

	//소유한 몽타주에서 노티파이 델리게이션 세팅
	for(FActionData ActionData : ActionDatas)
	{
		for(FAnimNotifyEvent AnimNotify : ActionData.Montage->Notifies)
		{
			if(AnimNotify.Notify != nullptr && AnimNotify.Notify->GetClass() == UCAN_EndAction::StaticClass())
			{
				Cast<UCAN_EndAction>(AnimNotify.Notify)->OnEndAction.BindUObject(this, &UCAction_Base::EndAction);
			}
		}
	}
}

void UCAction_Base::SetDirectionToCamera() const
{
	const UCameraComponent* Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	if(Camera == nullptr)
	{
		return;
	}

	FVector NewVector = Camera->GetForwardVector();
	NewVector.Z = OwnerCharacter->GetActorForwardVector().Z;
	OwnerCharacter->SetActorRotation(NewVector.Rotation());
}