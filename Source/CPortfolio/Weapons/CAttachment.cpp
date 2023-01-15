#include "CAttachment.h"

#include "Global.h"
#include "Characters/CCharacter_Base.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
}

void ACAttachment::BeginPlay()
{	
	OwnerCharacter = Cast<ACCharacter_Base>(GetOwner());

	GetComponents<UShapeComponent>(Collisions);
	for (UShapeComponent* collision : Collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
		collision->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);
	}
	OffCollision();
	
	AttachTo(HolsterSocketName);
	Super::BeginPlay();
}

void ACAttachment::AttachTo(FName InSocketName)
{
	if(InSocketName.IsNone())
		return;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::OnCollision()
{
	for (UShapeComponent* collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	if(OnAttachmentCollision.IsBound())
		OnAttachmentCollision.Execute();
}

void ACAttachment::OffCollision()
{
	for (UShapeComponent* collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(OffAttachmentCollision.IsBound())
		OffAttachmentCollision.Execute();
}

void ACAttachment::OnEndEquip()
{
	AttachTo(HandSocketName);
}

void ACAttachment::OnEndUnEquip()
{
	AttachTo(HolsterSocketName);
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	OnAttachmentBeginOverlap.ExecuteIfBound(OwnerCharacter, this, Cast<ACCharacter_Base>(OtherActor));
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());
	
	OnAttachmentEndOverlap.ExecuteIfBound(OwnerCharacter, this, Cast<ACCharacter_Base>(OtherActor));
}