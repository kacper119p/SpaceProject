// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "SpaceShipMovement.h"


// Sets default values for this component's properties
USpaceShipMovement::USpaceShipMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USpaceShipMovement::BeginPlay()
{
	Super::BeginPlay();
}

void USpaceShipMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
