#include "CWeaponStructure.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"
#include "Components/CStatusComponent.h"
#include "Components/CStateComponent.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundCue.h"

void FActionContent::DoAction(ACCharacter_Base* InOwner)
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(InOwner);
	if (!!status)
		bCanMove ? status->Move() : status->Stop();

	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);

	if (bFixedCamera)
		status->EnableFixedCamera();
}

void FActionContent::EndAction(ACCharacter_Base* InOwner)
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(InOwner);
	if (!!status)
	{
		status->Move();
		status->DisableFixedCamera();
	}
	
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(InOwner);
	if (!!state)
		state->SetIdleMode();
}

void FActionContent::PlayEffect(ACCharacter_Base* InOwner)
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

void FActionContent::PlayEffect(USkeletalMeshComponent* InMesh, FName InSocketName)
{
	CheckNull(Effect);

	AActor* owner = InMesh->GetOwner();
	UWorld* world = owner->GetWorld();

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);

	CHelpers::PlayEffect(world, Effect, transform, InMesh, InSocketName);
}

///////////////////////////////////////////////////////////////////////////////

void FHitData::PlayMontage(ACharacter* InOwner)
{
	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(InOwner);
	if (!!status)
	{
		bCanMove ? status->Move() : status->Stop();
	}

	if (!!Montage)
		InOwner->PlayAnimMontage(Montage, PlayRatio);
	else
		InOwner->PlayAnimMontage(UCWeaponStructure::GetDefault_HitMontage(), PlayRatio);
}

void FHitData::PlayHitStop(UWorld* InWorld)
{
	CheckTrue(FMath::IsNearlyZero(StopTime));

	TArray<ACharacter*> characters;
	for (AActor* actor : InWorld->GetCurrentLevel()->Actors)
	{
		ACharacter* character = Cast<ACharacter>(actor);
		if (!!character)
			characters.Add(character);
	}

	//UGameplayStatics::SetGlobalTimeDilation(InWorld, 1e-3f);
	for (ACharacter* character : characters)
		character->CustomTimeDilation = 1e-3f;		


	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		//UGameplayStatics::SetGlobalTimeDilation(InWorld, 1);

		for (ACharacter* character : characters)
			character->CustomTimeDilation = 1;
	});

	FTimerHandle timerHandle;
	//InWorld->GetTimerManager().SetTimer(timerHandle, timerDelegate, StopTime * 1e-3f, false);
	InWorld->GetTimerManager().SetTimer(timerHandle, timerDelegate, StopTime, false);
}

void FHitData::PlaySoundCue(ACharacter* InOwner)
{
	CheckNull(SoundCue);

	UWorld* world = InOwner->GetWorld();
	FVector location = InOwner->GetActorLocation();

	UGameplayStatics::SpawnSoundAtLocation(world, SoundCue, location);
}

void FHitData::PlayEffect(UWorld* InWorld, const FVector& InLocation)
{
	CheckNull(Effect);

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);
	transform.AddToTranslation(InLocation);

	CHelpers::PlayEffect(InWorld, Effect, transform);
}

void FHitData::SendDamage(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	FActionDamageEvent e;
	e.HitData = this;

	InOtherCharacter->TakeDamage(Power, e, InAttacker->GetController(), InAttackCauser);
}

///////////////////////////////////////////////////////////////////////////////


UAnimMontage* UCWeaponStructure::Default_HitMontage = NULL;



UCWeaponStructure::UCWeaponStructure()
{
	CHelpers::GetAsset<UAnimMontage>(&Default_HitMontage, "AnimMontage'/Game/Character/Montages/Common/Stop_HitReaction_Montage.Stop_HitReaction_Montage'");
}
