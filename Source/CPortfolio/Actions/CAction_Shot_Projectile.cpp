#include "CAction_Shot_Projectile.h"
#include "CHelpers.h"

#include "ActionFunctions.h"

#include "Weapon.h"
#include "WeaponAttachment.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Effects/CProjectile_Collision.h"

UCAction_Shot_Projectile::UCAction_Shot_Projectile() : Super(), ProjectileHolsterSocket("ProjectileHolsterSocket"), ProjectileSocket("ProjectileSocket"), EventName("Draw")
{
}

void UCAction_Shot_Projectile::BeginPlay()
{
	Super::BeginPlay();

	//발사체의 콜리전 이벤트 등록
	for(uint8 P_Index = 0; P_Index < 3; P_Index++)
	{
		for(ACProjectile *Projectile : Projectiles[P_Index])
		{
			ACProjectile_Collision* Projectile_Collision = Cast<ACProjectile_Collision>(Projectile);
			if(Projectile_Collision != nullptr)
			{
				Projectile_Collision->OnProjectileCollision.BindUObject(this, &UCAction_Shot_Projectile::OnCollision);
			}
		}
	}

	//액션 이벤트 등록
	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	check(ActionComponent);

	ActionComponent->BindActionEvent(EventName, this);
}

/* 활시위를 매기는 동작 */
void UCAction_Shot_Projectile::BeginAction()
{
	//LineTrace와 달리 발사 프로세스가 없으므로 Super::BeginAction()을 부르지 않음
	UCAction_Base::BeginAction();

	//발사체 오브젝트 풀 인덱스 증가
	ProjectileIndex = (ProjectileIndex + 1) % 3;

	//활 시위를 매김
	for(uint8 U = 0; U < ProjectilesCount; U++)
	{
		Projectiles[ProjectileIndex][U]->SetActorTransform(FTransform());
		Projectiles[ProjectileIndex][U]->StopProjectile();
		Projectiles[ProjectileIndex][U]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ProjectileHolsterSocket);
		Projectiles[ProjectileIndex][U]->SetActorHiddenInGame(false);
	}

	//몽타주 재생
	if(ActionDatas.IsValidIndex(0))
	{
		ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
	}
	StateComponent->SetActionMode();
}

/* 화살을 발사함 */
void UCAction_Shot_Projectile::EndAction()
{
	Super::EndAction();

	//화살 발사
	for(uint8 U = 0; U < ProjectilesCount; U++)
	{
		Projectiles[ProjectileIndex][U]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Projectiles[ProjectileIndex][U]->Shoot();
	}
	StateComponent->SetIdleMode();
}

/* 액션 중이 아니면 Begin Action */
void UCAction_Shot_Projectile::KeyPressed()
{
	if(bActionEnded)
	{
		BeginAction();
	}
}

/* 발사체의 Collision 발생 시 데미지 전달 */
void UCAction_Shot_Projectile::OnCollision(AActor* InAttackCauser, AActor* InTargetActor)
{
	ActionFunctions::SendDamage(&HitData, OwnerCharacter, InAttackCauser, InTargetActor);
}

/* 활 시위를 매기는 이벤트 발생, 화살의 소켓 위치를 손으로 변경 */
void UCAction_Shot_Projectile::HandleEvent()
{
	for(uint8 U = 0; U < ProjectilesCount; U++)
	{
		Projectiles[ProjectileIndex][U]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ProjectileSocket);
	}

	//Weapon의 Attachment[0]의 Skeletal Mesh를 가져옴, 개선 필요
	UWeapon *Weapon = WeaponComponent->GetWeapon();
	if(Weapon == nullptr)
	{
		return;
	}
	if(Weapon->GetAttachments().IsValidIndex(0) && Weapon->GetAttachments()[0] != nullptr)
	{
		AttachmentMeshComponent = CHelpers::GetComponent<USkeletalMeshComponent>(Weapon->GetAttachments()[0]);
	}
	if(AttachmentMeshComponent != nullptr)
	{
		AttachmentMeshComponent->GetAnimInstance();
		
	}
}


