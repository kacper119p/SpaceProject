// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "SimpleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASimpleProjectile::ASimpleProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}

void ASimpleProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//OnEnabledEvent.AddDynamic(this, &ASimpleProjectile::OnObjectEnabled);
	MeshComponent->OnComponentHit.AddDynamic(this, &ASimpleProjectile::OnHit);
}

void ASimpleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (Timer >= LifeSpan)
	{
		Disable();
		Return();
	}
}

void ASimpleProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnEnabled()->RemoveDynamic(this, &ASimpleProjectile::OnObjectEnabled);
	MeshComponent->OnComponentHit.RemoveDynamic(this, &ASimpleProjectile::OnHit);
}

void ASimpleProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, TEXT("Hit"));

	Disable();
	HitEffectPool->Pull(GetActorLocation(), GetActorRotation());
	Return();
}

void ASimpleProjectile::OnObjectEnabled()
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * InitialSpeed);
}
