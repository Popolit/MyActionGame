#include "CANS_Collision.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CWeaponComponent.h"
#include "Weapons/CAttachment.h"

FString UCANS_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCANS_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComponent);

	TArray<ACAttachment*> const* attachments = weaponComponent->GetAttachments();
	CheckNull(attachments)
	for(ACAttachment* attachment : *(weaponComponent->GetAttachments()))
	{
		if(attachment == nullptr)
			continue;
		attachment->OnCollision();
	}
}

void UCANS_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComponent);

	TArray<ACAttachment*> const* attachments = weaponComponent->GetAttachments();
	CheckNull(attachments)
	for(ACAttachment* attachment : *(weaponComponent->GetAttachments()))
	{
		if(attachment == nullptr)
			continue;
		attachment->OffCollision();
	}
}

