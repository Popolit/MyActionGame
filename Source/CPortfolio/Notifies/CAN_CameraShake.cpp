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
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	CheckNull(CameraShakeClass);

	ACCharacter_Base* character =  Cast<ACCharacter_Base>(MeshComp->GetOwner());
	CheckNull(character);

	APlayerController* controller = character->GetController<APlayerController>();
	CheckNull(controller);

	controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);
}
