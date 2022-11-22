#include "FeetData.h"

FFeetData::FFeetData()
{
	LeftDistance = FVector::ZeroVector;
	RightDistance = FVector::ZeroVector;
	PelvisDistance = FVector::ZeroVector;
	LeftRotation = FRotator::ZeroRotator;
	RightRotation = FRotator::ZeroRotator;
}

FFeetData::FFeetData(FVector LeftDistance, FVector RightDistance, FVector PelvisDistance, FRotator LeftRotation,
	FRotator RightRotation)
{
	this->LeftDistance = LeftDistance;
	this->RightDistance = RightDistance;
	this->PelvisDistance = PelvisDistance;
	this->LeftRotation = LeftRotation;
	this->RightRotation = RightRotation;
}
