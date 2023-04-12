#include "CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCStatusComponent::UCStatusComponent() : Speed{400, 800}, MaxHealth(100.0f), bCanMove(true), bCanAction(true), bCanDash(true)
{
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCStatusComponent::Damage(float const& InAmount, float const& InStaggerTime)
{
	Health += (InAmount * -1.0f);
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if(OnDamaged.IsBound())
	{
		OnDamaged.Broadcast(InAmount, InStaggerTime);
	}
}

void UCStatusComponent::EnableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UCStatusComponent::DisableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}