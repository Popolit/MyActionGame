#include "ActionFunctions.h"
#include "CHelpers.h"

#include "Components/CStatusComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"


void ActionFunctions::DoAction(FActionData const& InActionData, ACharacter* InOwnerCharacter)
{
	if(InActionData.Montage == nullptr)
	{
		return;
	}

	InOwnerCharacter->PlayAnimMontage(InActionData.Montage, InActionData.PlayRatio);
	UCStatusComponent* StatusComponent = CHelpers::GetComponent<UCStatusComponent>(InOwnerCharacter);

	if (StatusComponent == nullptr)
	{
		return;
	}
	
	if(!InActionData.bCanMove)
	{
		StatusComponent->DisableMove();
	}
	if (InActionData.bFixedCamera)
	{
		StatusComponent->EnableFixedCamera();
	}
}

void ActionFunctions::EndAction(ACharacter* InOwnerCharacter)
{
	UCStatusComponent* StatusComponent = CHelpers::GetComponent<UCStatusComponent>(InOwnerCharacter);
	if (StatusComponent != nullptr)
	{
		StatusComponent->EnableMove();
		StatusComponent->DisableFixedCamera();
	}
}


void ActionFunctions::PlayHitEffect(FHitData const& InHitData, ACharacter* InAttacker, AActor* InTargetActor)
{
	//Effect
	if(InHitData.Effect == nullptr)
	{
		return;
	}

	const UWorld* World = InTargetActor->GetWorld();
	const FVector ActorLocation = InTargetActor->GetActorLocation();
	const FVector EffectLocation = ActorLocation + InTargetActor->GetActorRotation().RotateVector(InHitData.EffectLocation);


	FTransform Transform;
	Transform.SetLocation(EffectLocation);
	Transform.SetRotation(FQuat(InTargetActor->GetActorRotation()));
	Transform.SetScale3D(InHitData.EffectScale);

	UParticleSystem* Particle = Cast<UParticleSystem>(InHitData.Effect);
	UNiagaraSystem* Niagara = Cast<UNiagaraSystem>(InHitData.Effect);
	
	if (Particle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(InTargetActor->GetWorld(), Particle, Transform);
	}


	if (Niagara != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(InTargetActor->GetWorld(), Niagara, Transform.GetLocation(), FRotator(Transform.GetRotation()), Transform.GetScale3D());
	}

	// Sound
	if(InHitData.SoundCue != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(World, InHitData.SoundCue, ActorLocation);
	}

	//HitStop & ¿ª°æÁ÷
	const float OriginalTimeSpeed_Attacker = InAttacker->CustomTimeDilation;
	const float OriginalTimeSpeed_Target = InTargetActor->CustomTimeDilation;
	
	InAttacker->CustomTimeDilation = HitStopTimeSpeed;
	InTargetActor->CustomTimeDilation = HitStopTimeSpeed;

	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		InAttacker->CustomTimeDilation = OriginalTimeSpeed_Attacker;
		InTargetActor->CustomTimeDilation = OriginalTimeSpeed_Target;
	});

	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, InHitData.StopTime, false);
}

void ActionFunctions::SendDamage(FHitData* InHitData, ACharacter* InAttacker, AActor* InAttackCauser,
	AActor* InTargetActor)
{
	FActionDamageEvent DamageEvent;
	DamageEvent.HitData = InHitData;

	InTargetActor->TakeDamage(InHitData->Damage, DamageEvent, InAttacker->GetController(), InAttackCauser);
}
