// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "SimpleProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

ASimpleProjectile::ASimpleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	MeshComponent->SetSimulatePhysics(false);
	MeshComponent->SetEnableGravity(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovement->SetUpdatedComponent(MeshComponent);
}

void ASimpleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	OnEnabledEvent.AddDynamic(this, &ASimpleProjectile::OnObjectEnabled);
	OnDisabledEvent.AddDynamic(this, &ASimpleProjectile::OnObjectDisabled);
	MeshComponent->OnComponentHit.AddDynamic(this, &ASimpleProjectile::OnHit);
}

void ASimpleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (Timer >= LifeSpan)
	{
		Return();
	}
}

void ASimpleProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnEnabledEvent.RemoveDynamic(this, &ASimpleProjectile::OnObjectEnabled);
	OnDisabledEvent.RemoveDynamic(this, &ASimpleProjectile::OnObjectDisabled);
	MeshComponent->OnComponentHit.RemoveDynamic(this, &ASimpleProjectile::OnHit);
}

void ASimpleProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	HitEffectPool->Pull(GetActorLocation(), GetActorRotation());
	Return();
}

void ASimpleProjectile::OnObjectEnabled()
{
	Timer = 0;
	ProjectileMovement->SetUpdatedComponent(MeshComponent);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * InitialSpeed);
}

void ASimpleProjectile::OnObjectDisabled()
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::Zero());
	MeshComponent->SetPhysicsLinearVelocity(FVector::Zero());
	MeshComponent->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
}
