#include "CSubAnimInstance.h"
#include "CHelpers.h"

#include "Characters/Player/CPlayer.h"
#include "Components/CStateComponent.h"


void UCSubAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	//오너 캐릭터 세팅
	OwnerCharacter = Cast<ACCharacter_Base>(TryGetPawnOwner());
	if(OwnerCharacter == nullptr)
	{
		return;
	}

	//StateComponent 세팅
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	if(StateComponent == nullptr)
	{
		return;
	}

	//StateComponent의 델리게이션 세팅
	StateComponent->OnStateTypeChanged.AddUObject(this, &UCSubAnimInstance::OnStateTypeChanged);
	StateComponent->OnAerialConditionChanged.AddUObject(this, &UCSubAnimInstance::OnAerialConditionChanged);
}

/**
 * 애니메이션 업데이트 - 각 파라미터 갱신
 */
void UCSubAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(OwnerCharacter == nullptr)
	{
		return;
	}

	//갱신
	bIsInAir = StateComponent->IsInAir();
	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
	AimPitch = OwnerCharacter->GetAimPitch();

}

/**
 * 오너 캐릭터의 상태 변경
 * @param NewStateType 변경된 상태
 */
void UCSubAnimInstance::OnStateTypeChanged(EStateType NewStateType)
{
	StateType = NewStateType;
}

/**
 * 오너 캐릭터의 체공 상태 변경
 * @param IsInAir 체공 상태, true = 공중에 뜸
 */
void UCSubAnimInstance::OnAerialConditionChanged(bool IsInAir)
{
	bIsInAir = IsInAir;
}
