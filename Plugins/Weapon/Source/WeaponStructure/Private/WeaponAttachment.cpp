#include "WeaponAttachment.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

/* Collision ä���� �߰��ϵ��� ���� �ʿ� */
AWeaponAttachment::AWeaponAttachment() : HolsterSocketName("Root"), EquipSocketName("Root")
{
	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(Root);
}

void AWeaponAttachment::BeginPlay()
{
	//���� ĳ���� ��������
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//�ݸ��� ������Ʈ�� ��� Collisions�� ���
	GetComponents<UShapeComponent>(Collisions);

	//��� �ݸ����� �������̼� ���
	for(UShapeComponent* Collision : Collisions)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentBeginOverlap);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentEndOverlap);
	}
	
	OffCollision();
	AttachTo(HolsterSocketName);
}


/* �ݸ����� �� */
void AWeaponAttachment::OnCollision()
{
	for (UShapeComponent* Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	if(OnWeaponAttachmentOnCollision.IsBound())
	{
		OnWeaponAttachmentOnCollision.Execute();
	}
}

/* �ݸ����� �� */
void AWeaponAttachment::OffCollision()
{
	for (UShapeComponent* Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if(OnWeaponAttachmentOffCollision.IsBound())
	{
		OnWeaponAttachmentOffCollision.Execute();
	}
}

//Equip�� �������ϰ� ���⸦ �տ� ���
void AWeaponAttachment::EndEquip()
{
	AttachTo(EquipSocketName);
}


//UnEquip�� �������ϰ� ���⸦ ��� ����
void AWeaponAttachment::EndUnEquip()
{
	AttachTo(HolsterSocketName);
}

//�ݸ��� �̺�Ʈ �� BeginOverlap �߻�
void AWeaponAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OwnerCharacter == OtherActor)
	{
		return;
	}

	if(OnWeaponAttachmentBeginOverlap.IsBound())
	{
		OnWeaponAttachmentBeginOverlap.Execute(this, OtherActor);
	}
}

//�ݸ��� �̺�Ʈ �� EndOverlap �߻�
void AWeaponAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OwnerCharacter == OtherActor)
	{
		return;
	}
	
	if(OnWeaponAttachmentEndOverlap.IsBound())
	{
		OnWeaponAttachmentEndOverlap.Execute(this, OtherActor);
	}
}

//���Ͽ� ���͸� ����
void AWeaponAttachment::AttachTo(FName InSocketName)
{
	if(InSocketName.IsNone())
	{
		return;
	}
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}