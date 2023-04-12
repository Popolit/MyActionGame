#include "CAction_Zoom.h"

#include "CHelpers.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

UCAction_Zoom::UCAction_Zoom()
{
}

void UCAction_Zoom::BeginPlay()
{
	Super::BeginPlay();

	check(OwnerCharacter);
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	check(StateComponent);

	StatusComponent = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	check(StatusComponent);

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	if(SpringArm == nullptr || Camera == nullptr)
	{
		return;
	}
	
	FOnTimelineFloat TimelineFloat;
	TimelineFloat.BindUFunction(this, "OnAiming");
	
	Timeline.AddInterpFloat(Curve, TimelineFloat);
	Timeline.SetPlayRate(200);
}

void UCAction_Zoom::BeginAction()
{
	Super::BeginAction();

}

void UCAction_Zoom::EndAction()
{
	Super::EndAction();
}

void UCAction_Zoom::KeyPressed()
{
	if(StateComponent->IsIdleMode())
	{
		StateComponent->SetSubActionMode();
		StatusComponent->DisableDash();
	
		if(SpringArm == nullptr || Camera == nullptr)
		{
			return;
		}
		OriginData.TargetArmLength = SpringArm->TargetArmLength;
		OriginData.SocketOffset = SpringArm->SocketOffset;
		OriginData.bEnableCameraLag = SpringArm->bEnableCameraLag;

		SpringArm->TargetArmLength = AimData.TargetArmLength;
		SpringArm->SocketOffset = AimData.SocketOffset;
		SpringArm->bEnableCameraLag = AimData.bEnableCameraLag;

		Timeline.PlayFromStart();
	}
}

void UCAction_Zoom::KeyReleased()
{
	StateComponent->SetIdleMode();
	StatusComponent->EnableDash();
	
	if(SpringArm == nullptr || Camera == nullptr)
	{
		return;
	}
	SpringArm->TargetArmLength = OriginData.TargetArmLength;
	SpringArm->SocketOffset = OriginData.SocketOffset;
	SpringArm->bEnableCameraLag = OriginData.bEnableCameraLag;

	Timeline.ReverseFromEnd();
}

void UCAction_Zoom::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

TStatId UCAction_Zoom::GetStatId() const
{
	return TStatId();
}

UWorld* UCAction_Zoom::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UCAction_Zoom::OnAiming(float InAmount) const
{
	Camera->FieldOfView = InAmount;
}


