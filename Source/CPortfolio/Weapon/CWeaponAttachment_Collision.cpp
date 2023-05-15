#include "CWeaponAttachment_Collision.h"

#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

void ACWeaponAttachment_Collision::BeginPlay()
{
	Super::BeginPlay();

	//콜리전 컴포넌트를 모두 Collisions에 등록
	GetComponents<UShapeComponent>(Collisions);
	
	//모든 콜리전의 델리게이션 등록
	for(UShapeComponent* Collision : Collisions)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentBeginOverlap);
		Collision->OnComponentEndOverlap.AddDynamic(this, &AWeaponAttachment::OnComponentEndOverlap);
	}

		
	DisableCollision();
}

/* 콜리전을 켬 */
void ACWeaponAttachment_Collision::EnableCollision()
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
void ACWeaponAttachment_Collision::DisableCollision()
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

//콜리전 이벤트 중 BeginOverlap 발생
void ACWeaponAttachment_Collision::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
void ACWeaponAttachment_Collision::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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