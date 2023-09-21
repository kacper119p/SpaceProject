// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "SpaceShipCannon.h"

#include "Weapons/Weapon.h"

USpaceShipCannon::USpaceShipCannon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpaceShipCannon::Shoot()
{
	WeaponInstance->Shoot();
}

void USpaceShipCannon::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponInstance = NewObject<UObject>(this, Weapon);
	check(GetWorld());
	WeaponInstance->Initialize(this);
	WeaponInstance->BeginPlay();
}

void USpaceShipCannon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	WeaponInstance->EndPlay(EndPlayReason);
}


void USpaceShipCannon::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	WeaponInstance->Tick(DeltaTime);
}
