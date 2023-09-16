// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "ObjectPooling/PooledActor.h"

APooledActor::APooledActor()
{
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
	SetHidden(!bActive);
	SetActorEnableCollision(bActive);
	SetActorTickEnabled(bActive);
}

bool APooledActor::IsActive() const
{
	return bIsActive;
}
