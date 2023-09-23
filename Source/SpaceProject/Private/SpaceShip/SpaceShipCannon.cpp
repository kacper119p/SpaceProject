// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "SpaceShipCannon.h"

#include "NiagaraComponent.h"
#include "SpaceShipController.h"
#include "Weapons/Weapon.h"

USpaceShipCannon::USpaceShipCannon()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	MuzzleEffectEmitter = CreateDefaultSubobject<UNiagaraComponent>("Muzzle Effect Emitter");
	MuzzleEffectEmitter->SetupAttachment(this);
}


void USpaceShipCannon::SetController(ISpaceShipController* InController)
{
		Controller = CastChecked<UObject>(InController);
}


void USpaceShipCannon::Shoot()
{
	WeaponInstance->Shoot();
}


UNiagaraComponent* USpaceShipCannon::GetMuzzleEffectEmitter() const
{
	return MuzzleEffectEmitter;
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
	if(Controller->IsShooting())
	{
		Shoot();
	}
}
