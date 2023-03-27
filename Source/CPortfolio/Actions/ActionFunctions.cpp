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
		StatusComponent->Stop();
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
		StatusComponent->Move();
		StatusComponent->DisableFixedCamera();
	}
}


void ActionFunctions::PlayEffect(FActionData const& InActionData, ACharacter* InOwnerCharacter)
{
	if(InActionData.Effect == nullptr)
	{
		return;
	}

	FVector Location = InOwnerCharacter->GetActorLocation();
	Location += InOwnerCharacter->GetActorRotation().RotateVector(InActionData.EffectLocation);


	FTransform Transform;
	Transform.SetLocation(Location);
	Transform.SetRotation(FQuat(InOwnerCharacter->GetActorRotation()));
	Transform.SetScale3D(InActionData.EffectScale);

	UParticleSystem* Particle = Cast<UParticleSystem>(InActionData.Effect);
	UNiagaraSystem* Niagara = Cast<UNiagaraSystem>(InActionData.Effect);
	
	if (Particle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(InOwnerCharacter->GetWorld(), Particle, Transform);
		return;
	}


	if (Niagara != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(InOwnerCharacter->GetWorld(), Niagara, Transform.GetLocation(), FRotator(Transform.GetRotation()), Transform.GetScale3D());
	}
}
