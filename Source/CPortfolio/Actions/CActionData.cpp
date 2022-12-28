#include "CActionData.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CStatusComponent.h"

void FActionMontage::DoAction(ACCharacter_Base* InOwner) const
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(InOwner);
	if (!!status)
		bCanMove ? status->Move() : status->Stop();

	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);

	if (bFixedCamera)
		status->EnableFixedCamera();
}


void FActionMontage::PlayEffect(ACCharacter_Base* InOwner) const
{
	CheckNull(Effect);

	FVector location = EffectLocation;
	FVector scale = EffectScale;

	FVector ownerLocation = InOwner->GetActorLocation();
	ownerLocation += InOwner->GetActorRotation().RotateVector(location);

	
	FTransform transform;
	transform.SetLocation(ownerLocation);
	transform.SetRotation(FQuat(InOwner->GetActorRotation()));
	transform.SetScale3D(scale);

	CHelpers::PlayEffect(InOwner->GetWorld(), Effect, transform);
}

void FActionMontage::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName) const
{
	CheckNull(Effect);

	AActor* owner = InMesh->GetOwner();
	UWorld* world = owner->GetWorld();

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);

	CHelpers::PlayEffect(world, Effect, transform, InMesh, InSocketName);
}

UCAction* UCActionData::GetAction(FActionTrigger const& Trigger)
{
	if(!Actions.Contains(Trigger))
		return nullptr;
	UCAction** ptrAction = Actions.Find(Trigger);
	return *ptrAction;
}
