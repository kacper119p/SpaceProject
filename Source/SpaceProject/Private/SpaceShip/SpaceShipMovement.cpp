// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "SpaceShipMovement.h"
#include "SpaceShipController.h"
#include "VectorUtil.h"

USpaceShipMovement::USpaceShipMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void USpaceShipMovement::Attach(UPrimitiveComponent* const InControlled)
{
	Controlled = InControlled;
}

void USpaceShipMovement::SetController(ISpaceShipController * InController)
{
	Controller = CastChecked<UObject>(InController);
}

void USpaceShipMovement::HandleRotation(const FRotator& Rotation, float const DeltaTime)
{
	Controlled->AddWorldRotation(Rotation * MaxRotationSpeed * DeltaTime);
}

void USpaceShipMovement::BeginPlay()
{
	Super::BeginPlay();
}

void USpaceShipMovement
::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleThrust(Controller->GetThrust());
	HandleRotation(Controller->GetRotation(), DeltaTime);
}

void USpaceShipMovement::HandleThrust(float Thrust)
{
	Thrust = UE::Geometry::VectorUtil::Clamp(Thrust, -1.0f, 1.0f);
	const FVector MoveDirectionWorld
		= Controlled->GetComponentTransform()
		            .TransformVector(FVector(Thrust, 0, 0))
		            .GetSafeNormal();

	Controlled->AddForce(MoveDirectionWorld * MaxThrust, NAME_None, true);
}
