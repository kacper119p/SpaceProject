// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "HitEffect.h"

#include "NiagaraComponent.h"

AHitEffect::AHitEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("VFX");
	RootComponent = NiagaraComponent;
	
	NiagaraComponent->Deactivate();
}


void AHitEffect::BeginPlay()
{
	Super::BeginPlay();
	OnEnabledEvent.AddDynamic(this, &AHitEffect::OnObjectEnabled);
}

void AHitEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnEnabledEvent.RemoveDynamic(this, &AHitEffect::OnObjectEnabled);
}

void AHitEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (Timer > LifeTime)
	{
		Return();
	}
}

void AHitEffect::OnObjectEnabled()
{
	NiagaraComponent->Activate(true);
	Timer = 0;
}
