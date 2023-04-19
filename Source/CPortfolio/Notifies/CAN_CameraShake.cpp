#include "CAN_CameraShake.h"
#include "CHelpers.h"

#include "Characters/CCharacter_Base.h"

UCAN_CameraShake::UCAN_CameraShake()
{
	CameraShakeClass = UMatineeCameraShake::StaticClass();
}

FString UCAN_CameraShake::GetNotifyName_Implementation() const
{
	return "Camera Shake";
}

void UCAN_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if(MeshComp == nullptr || MeshComp->GetOwner())
	{
		return;
	}

	if(CameraShakeClass == nullptr)
	{
		return;
	}

	ACCharacter_Base* Character =  Cast<ACCharacter_Base>(MeshComp->GetOwner());
	if(Character == nullptr)
	{
		return;
	}

	APlayerController* PlayerController = Character->GetController<APlayerController>();
	if(PlayerController == nullptr)
	{
		return;
	}

	PlayerController->PlayerCameraManager->StartCameraShake(CameraShakeClass);
}
