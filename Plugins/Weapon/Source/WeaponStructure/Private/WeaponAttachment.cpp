#include "WeaponAttachment.h"

#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Components/ShapeComponent.h"

/* Collision 채널을 추가하도록 수정 필요 */
AWeaponAttachment::AWeaponAttachment() : HolsterSocketName("Root"), EquipSocketName("Root")
{
	Root = this->CreateDefaultSubobject<USceneComponent>("Root");
	this->SetRootComponent(Root);
}

void AWeaponAttachment::BeginPlay()
{
	//오너 캐릭터 가져오기
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//콜리전 컴포넌트를 모두 Collisions에 등록
	GetComponents<UShapeComponent>(Collisions);

	//모든 콜리전의 델리게이션 등록
	for(UShapeComponent* Collision : Collisions)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentBeginOverlap);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentEndOverlap);
	}
	
	OffCollision();
	AttachTo(HolsterSocketName);
}


/* 콜리전을 켬 */
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

/* 콜리전을 끔 */
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

//Equip을 마무리하고 무기를 손에 장비
void AWeaponAttachment::EndEquip()
{
	AttachTo(EquipSocketName);
}


//UnEquip을 마무리하고 무기를 장비 해제
void AWeaponAttachment::EndUnEquip()
{
	AttachTo(HolsterSocketName);
}

//콜리전 이벤트 중 BeginOverlap 발생
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

//콜리전 이벤트 중 EndOverlap 발생
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

//소켓에 액터를 붙임
void AWeaponAttachment::AttachTo(FName InSocketName)
{
	if(InSocketName.IsNone())
	{
		return;
	}
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}