// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "SpaceDust.h"

ASpaceDust::ASpaceDust()
{
	PrimaryActorTick.bCanEverTick = false;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("VFX");
	RootComponent = NiagaraComponent;

	FollowPlayerComponent = CreateDefaultSubobject<UFollowPlayerComponent>("Follow Player");
}
