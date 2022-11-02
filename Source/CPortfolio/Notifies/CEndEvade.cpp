#include "Notifies/CEndEvade.h"
#include "Global.h"

#include "Characters/Player/CPlayer.h"

FString UCEndEvade::GetNotifyName_Implementation() const
{
	return "End_Evade";
}

void UCEndEvade::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	player->EndEvade();
}
