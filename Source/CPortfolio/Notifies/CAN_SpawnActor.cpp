#include "CAN_SpawnActor.h"

UCAN_SpawnActor::UCAN_SpawnActor() : NotifyName("SpawnActor")
{
}

FString UCAN_SpawnActor::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCAN_SpawnActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
}
