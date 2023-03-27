#include "CANS_MakeFlyingMode.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCANS_MakeFlyingMode::UCANS_MakeFlyingMode() : NotifyName("MakeFlyingMode")
{
}

FString UCANS_MakeFlyingMode::GetNotifyName_Implementation() const
{
	return NotifyName;
}

void UCANS_MakeFlyingMode::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
	{
		return;
	}

	ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if(OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
}

void UCANS_MakeFlyingMode::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if(MeshComp == nullptr || MeshComp->GetOwner() == nullptr)
	{
		return;
	}
	
	ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	if(OwnerCharacter != nullptr)
	{
		OwnerCharacter->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		
	}
}
