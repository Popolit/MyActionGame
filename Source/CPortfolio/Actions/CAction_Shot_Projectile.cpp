#include "CAction_Shot_Projectile.h"
#include "CHelpers.h"

#include "ActionFunctions.h"

#include "Weapon.h"
#include "WeaponAttachment.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Effects/CProjectile_Collision.h"

UCAction_Shot_Projectile::UCAction_Shot_Projectile() : Super(), ProjectileHolsterSocket("ProjectileHolsterSocket"), ProjectileSocket("ProjectileSocket"), EventName("Draw")
{
}

void UCAction_Shot_Projectile::BeginPlay()
{
	Super::BeginPlay();

	for(ACProjectile *Projectile : Projectiles)
	{
		ACProjectile_Collision* Projectile_Collision = Cast<ACProjectile_Collision>(Projectile);
		if(Projectile_Collision != nullptr)
		{
			Projectile_Collision->OnProjectileCollision.BindUObject(this, &UCAction_Shot_Projectile::OnCollision);
		}
	}

	UCActionComponent* ActionComponent = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	check(ActionComponent);

	ActionComponent->BindActionEvent(EventName, this);
}

void UCAction_Shot_Projectile::BeginAction()
{
	UCAction_Base::BeginAction();

	ProjectileIndex = (ProjectileIndex + 1) % 3;
	for(uint8 U = ProjectilesCount * ProjectileIndex; U < ProjectilesCount * (ProjectileIndex + 1); U++)
	{
		Projectiles[U]->SetActorTransform(FTransform());
		Projectiles[U]->StopProjectile();
		Projectiles[U]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ProjectileHolsterSocket);
		Projectiles[U]->SetActorHiddenInGame(false);
	}
	
	if(ActionDatas.IsValidIndex(0))
	{
		ActionFunctions::DoAction(ActionDatas[0], OwnerCharacter);
	}
	StateComponent->SetActionMode();
}

void UCAction_Shot_Projectile::EndAction()
{
	Super::EndAction();
	for(uint8 U = ProjectilesCount * ProjectileIndex; U < ProjectilesCount * (ProjectileIndex + 1); U++)
	{
		Projectiles[U]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Projectiles[U]->Shoot();
	}
	StateComponent->SetIdleMode();
}

void UCAction_Shot_Projectile::KeyPressed()
{
	if(bActionEnded)
	{
		BeginAction();
	}
}

void UCAction_Shot_Projectile::OnCollision(AActor* InAttackCauser, AActor* InTargetActor)
{
	ActionFunctions::SendDamage(&HitData, OwnerCharacter, InAttackCauser, InTargetActor);
}

void UCAction_Shot_Projectile::HandleEvent()
{
	for(uint8 U = ProjectilesCount * ProjectileIndex; U < ProjectilesCount * (ProjectileIndex + 1); U++)
	{
		Projectiles[U]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ProjectileSocket);
	}
}


