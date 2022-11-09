#include "CAttack.h"

#include "Global.h"

#include "Weapons/CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"

UCAttack::UCAttack()
{

}

void UCAttack::BeginPlay(ACAttachment* InAttachment, ACharacter* InOwner, const TArray<FAttackData>& InAttackDatas, const TArray<FHitData>& InHitDatas)
{
	OwnerCharacter = InOwner;
	World = OwnerCharacter->GetWorld();

	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	AttackDatas = InAttackDatas;
	HitDatas = InHitDatas;
}

void UCAttack::Begin_Attack()
{
	bBeginAction = true;
}

void UCAttack::End_Attack()
{
	bBeginAction = false;
}