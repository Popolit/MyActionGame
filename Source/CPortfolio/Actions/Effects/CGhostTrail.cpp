#include "CGhostTrail.h"

#include "CHelpers.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACGhostTrail::ACGhostTrail()
{
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &Mesh, "Mesh");
}

/* Ghost Trail 생성 */
void ACGhostTrail::BeginPlay()
{
	Super::BeginPlay();

	//수명 세팅
	SetLifeSpan(LifeSpan);
	
	Mesh->SetVisibility(false);

	//고스트 트레일 잔상 효과 세팅
	Material = UMaterialInstanceDynamic::Create(MaterialInstance, this);
	Material->SetVectorParameterValue("Color", Color);
	Material->SetScalarParameterValue("Exp", Exp);

	//PosableMesh에 복사
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Mesh->SetSkeletalMesh(OwnerCharacter->GetMesh()->SkeletalMesh);
	Mesh->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());

	//모든 머티리얼을 GhostTrail 머티리얼로 변경
	for (int32 i = 0; i < OwnerCharacter->GetMesh()->SkeletalMesh->Materials.Num(); i++)
	{
		Mesh->SetMaterial(i, Material);
	}


	//타이머 람다 함수
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateLambda([=]()
	{
		if (Mesh->IsVisible() == false)
		{
			Mesh->ToggleVisibility();
		}
		
		float Height = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SetActorLocation(OwnerCharacter->GetActorLocation() - FVector(0, 0, Height));
		SetActorRotation(OwnerCharacter->GetActorRotation() + FRotator(0, -90, 0));
		
		Mesh->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());
	});

	//Interval 시간 마다 람다 함수 실행
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Interval, true, StartDelay);
}

/* EndPlay 호출 시 타이머 초기화 */
void ACGhostTrail::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}