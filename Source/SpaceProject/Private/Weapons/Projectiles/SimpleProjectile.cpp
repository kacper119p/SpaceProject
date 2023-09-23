// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "SimpleProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASimpleProjectile::ASimpleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	RootComponent = CollisionComponent;

	CollisionComponent->SetSimulatePhysics(false);
	CollisionComponent->SetEnableGravity(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovement->SetUpdatedComponent(CollisionComponent);
}

void ASimpleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	OnEnabledEvent.AddDynamic(this, &ASimpleProjectile::OnObjectEnabled);
	OnDisabledEvent.AddDynamic(this, &ASimpleProjectile::OnObjectDisabled);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASimpleProjectile::OnHit);
}

void ASimpleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (Timer >= LifeTime)
	{
		Return();
	}
}

void ASimpleProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnEnabledEvent.RemoveDynamic(this, &ASimpleProjectile::OnObjectEnabled);
	OnDisabledEvent.RemoveDynamic(this, &ASimpleProjectile::OnObjectDisabled);
	CollisionComponent->OnComponentHit.RemoveDynamic(this, &ASimpleProjectile::OnHit);
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
	ProjectileMovement->SetUpdatedComponent(CollisionComponent);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * ProjectileMovement->InitialSpeed);
}

void ASimpleProjectile::OnObjectDisabled()
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::Zero());
	CollisionComponent->SetPhysicsLinearVelocity(FVector::Zero());
	CollisionComponent->SetPhysicsAngularVelocityInDegrees(FVector::Zero());
}
