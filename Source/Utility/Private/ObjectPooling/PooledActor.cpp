// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "ObjectPooling/PooledActor.h"

#include "ObjectPooling/ObjectPool.h"

APooledActor::APooledActor()
{
}

void APooledActor::Initialize(UObjectPool* InPool)
{
	ObjectPool = InPool;
}

void APooledActor::Enable()
{
	SetActive(true);
}

void APooledActor::Disable()
{
	SetActive(false);
}

void APooledActor::SetActive(const bool bActive)
{
	bIsActive = bActive;
	SetActorHiddenInGame(!bActive);
	SetActorEnableCollision(bActive);
	SetActorTickEnabled(bActive);
	
	if(bActive)
	{
		OnEnabledEvent.Broadcast();
	}
	else
	{
		OnDisabledEvent.Broadcast();
	}
}

bool APooledActor::IsActive() const
{
	return bIsActive;
}

void APooledActor::Return()
{
	SetActive(false);
	ObjectPool->Return(this);
}
