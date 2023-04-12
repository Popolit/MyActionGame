#include "CEnemy.h"
#include "CHelpers.h"

#include "Components/CAIBehaviorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACEnemy::ACEnemy() : ACCharacter_Base()
{
	CHelpers::CreateActorComponent<UCAIBehaviorComponent>(this, &BehaviorComponent, "Behavior");

	GetCharacterMovement()->MaxWalkSpeed /= 2;
}
