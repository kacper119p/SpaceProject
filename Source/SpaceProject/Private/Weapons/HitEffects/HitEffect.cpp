// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "HitEffect.h"

AHitEffect::AHitEffect()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AHitEffect::BeginPlay()
{
	Super::BeginPlay();
	//OnEnabledEvent.AddDynamic(this, &AHitEffect::OnObjectEnabled);
}

void AHitEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (Timer > Lifespan)
	{
		Return();
	}
}

void AHitEffect::OnObjectEnabled()
{
	Timer = 0;
}
