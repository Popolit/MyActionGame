#include "CAction_Base.h"

#include "CHelpers.h"
#include "Notifies/CAN_EndAction.h"

/**
 * BeginPlay - 액션이 사용중인 몽타주에 EndAction 노티파이가 있으면
 * 해당 노티파이의 델리게이션을 세팅
 */
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

/**
 * 캐릭터의 방향을 카메라 방향으로 수정
 * Todo : 이 함수를 ActionFunctions로 옮기기
 */
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