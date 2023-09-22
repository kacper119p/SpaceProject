// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Projectiles/Projectile.h"
#include "SimpleProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SPACEPROJECT_API ASimpleProjectile : public AProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Characteristics")
	float InitialSpeed;

	UPROPERTY(EditAnywhere, Category = "Characteristics")
	float LifeSpan;

	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
	
private:
	float Timer;
public:
	ASimpleProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	           UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnObjectEnabled();
	UFUNCTION()
	void OnObjectDisabled();
};
