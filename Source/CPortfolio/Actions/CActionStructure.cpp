#include "CActionStructure.h"
#include "Global.h"

#include "Sound/SoundCue.h"

#include "Characters/CCharacter_Base.h"


void FHitData::PlayHitStop(UWorld* InWorld) const
{
	CheckTrue(FMath::IsNearlyZero(StopTime));

	TArray<ACCharacter_Base*> characters;
	for (AActor* actor : InWorld->GetCurrentLevel()->Actors)
	{
		ACCharacter_Base* character = Cast<ACCharacter_Base>(actor);
		if (!!character)
			characters.Add(character);
	}

	for (ACCharacter_Base* character : characters)
		character->CustomTimeDilation = 0.0001f;		


	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
	{

		for (ACCharacter_Base* character : characters)
			character->CustomTimeDilation = 1.0f;
	});

	FTimerHandle timerHandle;
	InWorld->GetTimerManager().SetTimer(timerHandle, timerDelegate, StopTime, false);
}

void FHitData::PlaySoundCue(ACCharacter_Base* InOwner) const
{
	CheckNull(SoundCue);
	UWorld* world = InOwner->GetWorld();
	FVector location = InOwner->GetActorLocation();

	UGameplayStatics::SpawnSoundAtLocation(world, SoundCue, location);
}

void FHitData::PlayEffect(UWorld* InWorld, const FVector& InLocation) const
{
	CheckNull(Effect);

	FTransform transform;
	transform.SetLocation(EffectLocation);
	transform.SetScale3D(EffectScale);
	transform.AddToTranslation(InLocation);

	CHelpers::PlayEffect(InWorld, Effect, transform);
}

void FHitData::SendDamage(ACCharacter_Base* InAttacker, AActor* InAttackCauser, ACCharacter_Base* InOtherCharacter)
{
	FActionDamageEvent e;
	e.HitData = this;

	InOtherCharacter->TakeDamage(Damage, e, InAttacker->GetController(), InAttackCauser);
}
