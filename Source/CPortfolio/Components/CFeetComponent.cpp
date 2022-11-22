#include "CFeetComponent.h"
#include "Global.h"

#include "Characters/CCharacter_Base.h"

#include "CollisionQueryParams.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"


UCFeetComponent::UCFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACCharacter_Base>(GetOwner());
}

void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplyIK(DeltaTime);
}

//발 IK를 위한 지면 LineTrace 결과를 반환
void UCFeetComponent::Trace(FName const& InSocketName, float& OutDistance, FRotator& OutRotator)
{
	FVector socketLocation = Owner->GetMesh()->GetSocketLocation(InSocketName);
	FVector actorLocation = Owner->GetActorLocation();

	FVector startLocation = FVector(socketLocation.X, socketLocation.Y, actorLocation.Z);

	float halfToFloor = startLocation.Z - Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - TraceDistance;
	FVector endLocation = FVector(socketLocation.X, socketLocation.Y, halfToFloor);

	FHitResult result = FHitResult();
	
	bool isTraced = GetWorld()->LineTraceSingleByChannel
		(result
			, startLocation
			, endLocation
			, ECollisionChannel::ECC_Visibility
			, FCollisionQueryParams(NAME_None, true, Owner)
		);

	if(!isTraced)
		return;

	OutDistance = (result.ImpactPoint - result.TraceEnd).Size() + OffsetDistance - TraceDistance;
	OutRotator.Roll = UKismetMathLibrary::DegAtan2(result.ImpactNormal.Y, result.ImpactNormal.Z);
	OutRotator.Pitch = -(UKismetMathLibrary::DegAtan2(result.ImpactNormal.X, result.ImpactNormal.Z));
}

void UCFeetComponent::ApplyIK(float DeltaTime)
{
	float leftDistance = 0.0f;
	float rightDistance = 0.0f;
	FRotator leftRotation = FRotator::ZeroRotator;
	FRotator rightRotation = FRotator::ZeroRotator;
	
	Trace(LeftFootName, leftDistance, leftRotation);
	Trace(RightFootName, rightDistance, rightRotation);
	float const pelvisHeight = FMath::Min(leftDistance, rightDistance);
	
	FeetData.LeftRotation = UKismetMathLibrary::RInterpTo(FeetData.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	FeetData.RightRotation = UKismetMathLibrary::RInterpTo(FeetData.RightRotation, rightRotation, DeltaTime, InterpSpeed);
	FeetData.LeftDistance.X = UKismetMathLibrary::FInterpTo(FeetData.LeftDistance.X, leftDistance - pelvisHeight, DeltaTime, InterpSpeed);
	FeetData.RightDistance.X = UKismetMathLibrary::FInterpTo(FeetData.RightDistance.X, -(rightDistance - pelvisHeight), DeltaTime, InterpSpeed);
	FeetData.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(FeetData.PelvisDistance.Z, pelvisHeight, DeltaTime, InterpSpeed);
}

