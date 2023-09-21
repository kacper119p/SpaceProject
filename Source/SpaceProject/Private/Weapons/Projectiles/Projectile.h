// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "ObjectPooling/ObjectPool.h"
#include "ObjectPooling/PooledActor.h"
#include "Projectile.generated.h"

class UObjectPool;

UCLASS()
class AProjectile : public APooledActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UObjectPool* HitEffectPool;

public:
	void Initialize(UObjectPool* InPool, UObjectPool* InHitEffectPoll);
	void Shoot(const FVector& Location, const FRotator& Rotation);
	virtual void OnShoot();
};
