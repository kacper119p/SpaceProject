// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "Movement/RandomRotation.h"
#include "Kismet/KismetMathLibrary.h"


URandomRotation::URandomRotation()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;

	MinRotationSpeed = 0;
	MaxRotationSpeed = 0;
}


void URandomRotation::BeginPlay()
{
	Super::BeginPlay();

	FVector RotationVector
		= FVector(FMath::RandRange(-1.0f, 1.0f),
		          FMath::RandRange(-1.0f, 1.0f),
		          FMath::RandRange(-1.0f, 1.0f));

	RotationVector = RotationVector.GetSafeNormal();

	Rotation = UKismetMathLibrary::RotatorFromAxisAndAngle(
		RotationVector, FMath::RandRange(MinRotationSpeed, MaxRotationSpeed));
}


void URandomRotation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetOwner()->AddActorWorldRotation(Rotation * DeltaTime);
}
