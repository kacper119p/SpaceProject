// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "ProjectileWeapon.h"

#include "NiagaraComponent.h"
#include "ObjectPooling/ObjectPool.h"
#include "Projectiles/Projectile.h"
#include "SpaceShip/SpaceShipCannon.h"

UProjectileWeapon::UProjectileWeapon()
{
}

void UProjectileWeapon::Initialize(USpaceShipCannon* Owner)
{
	Cannon = Owner;
	UNiagaraComponent* Emitter = Cannon->GetMuzzleEffectEmitter();
	Emitter->SetAsset(MuzzleEffect);
	Emitter->Deactivate();
	
}

void UProjectileWeapon::Tick(float const DeltaTime)
{
	Timer += DeltaTime;
}

void UProjectileWeapon::Shoot()
{
	if (Timer >= Cooldown)
	{
		Cannon->GetMuzzleEffectEmitter()->Activate(true);
		ProjectilePool->Pull(Cannon->GetComponentLocation(), Cannon->GetComponentRotation());
		Timer = 0;
	}
}

void UProjectileWeapon::BeginPlay()
{
	Timer = Cooldown;

	ProjectilePool = NewObject<UObjectPool>(this);
	HitEffectPool = NewObject<UObjectPool>(this);

	ProjectilePool->Initialize(Projectile, ProjectilePoolSize);
	HitEffectPool->Initialize(HitEffect, HitEffectPoolSize);

	for (auto const Member : ProjectilePool->GetMembers())
	{
		Cast<AProjectile>(Member)->Initialize(ProjectilePool, HitEffectPool);
	}
}

void UProjectileWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ProjectilePool->Dispose();
	HitEffectPool->Dispose();
}
