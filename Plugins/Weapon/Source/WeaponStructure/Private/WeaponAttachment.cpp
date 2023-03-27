#include "WeaponAttachment.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

//Collision 채널을 추가하도록 수정 필요
AWeaponAttachment::AWeaponAttachment() : HolsterSocketName("Root"), EquipSocketName("Root")
{
	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(Root);
}

void AWeaponAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	GetComponents<UShapeComponent>(Collisions);
	for(UShapeComponent* Collision : Collisions)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentBeginOverlap);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentEndOverlap);
	}
	
	OffCollision();
	AttachTo(HolsterSocketName);
}

void AWeaponAttachment::OnCollision()
{
	for (UShapeComponent* Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	if(OnWeaponAttachmentCollision.IsBound())
	{
		OnWeaponAttachmentCollision.Execute();
	}
}

void AWeaponAttachment::OffCollision()
{
	for (UShapeComponent* Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if(OffWeaponAttachmentCollision.IsBound())
	{
		OffWeaponAttachmentCollision.Execute();
	}
}

void AWeaponAttachment::EndEquip()
{
	AttachTo(EquipSocketName);
}


void AWeaponAttachment::EndUnEquip()
{
	AttachTo(HolsterSocketName);
}

void AWeaponAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnWeaponAttachmentBeginOverlap.ExecuteIfBound(OwnerCharacter, this, OtherActor);
}

void AWeaponAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnWeaponAttachmentEndOverlap.ExecuteIfBound(OwnerCharacter, this, OtherActor);
}

void AWeaponAttachment::AttachTo(FName InSocketName)
{
	if(InSocketName.IsNone())
	{
		return;
	}
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}