// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "Projectile.h"

void AProjectile::Initialize(UObjectPool* InPool, UObjectPool* InHitEffectPoll)
{
	Super::Initialize(InPool);

	HitEffectPool = InHitEffectPoll;
}

void AProjectile::Shoot(const FVector& Location, const FRotator& Rotation)
{
	RootComponent->SetWorldLocationAndRotation(Location, Rotation);
	Enable();
	OnShoot();
}

void AProjectile::OnShoot()
{
}
