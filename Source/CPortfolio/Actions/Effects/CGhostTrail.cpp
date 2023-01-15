#include "CGhostTrail.h"

#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACGhostTrail::ACGhostTrail()
{
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &Mesh, "Mesh");
}

void ACGhostTrail::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
	
	Mesh->SetVisibility(false);
	
	Material = UMaterialInstanceDynamic::Create(MaterialInstance, this);
	Material->SetVectorParameterValue("Color", Color);
	Material->SetScalarParameterValue("Exp", Exp);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Mesh->SetSkeletalMesh(OwnerCharacter->GetMesh()->SkeletalMesh);
	Mesh->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());

	for (int32 i = 0; i < OwnerCharacter->GetMesh()->SkeletalMesh->Materials.Num(); i++)
		Mesh->SetMaterial(i, Material);


	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		if (Mesh->IsVisible() == false)
			Mesh->ToggleVisibility();

		
		float height = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SetActorLocation(OwnerCharacter->GetActorLocation() - FVector(0, 0, height));
		SetActorRotation(OwnerCharacter->GetActorRotation() + FRotator(0, -90, 0));
		
		Mesh->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, timerDelegate, Interval, true, StartDelay);
}

void ACGhostTrail::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}