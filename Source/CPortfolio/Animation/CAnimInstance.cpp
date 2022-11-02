#include "Animation/CAnimInstance.h"
#include "Global.h"

#include "GameFramework/Character.h"
#include "Characters/Player/CPlayer.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(Owner);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(Owner);

	IsInAir = Owner->GetIsInAir();
	Speed = Owner->GetVelocity().Size2D();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());
}
