// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "UObject/Object.h"
#include "ProjectileWeapon.generated.h"


class APooledActor;
class AProjectile;
class UNiagaraComponent;
class UObjectPool;
class IProjectile;
/**
 * 
 */
UCLASS(Blueprintable)
class SPACEPROJECT_API UProjectileWeapon : public UObject, public IWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	int32 ProjectilePoolSize = 32;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile>  Projectile;

	UPROPERTY(EditAnywhere)
	int32 HitEffectPoolSize = 32;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APooledActor> HitEffect;

	UPROPERTY(EditAnywhere)
	float Cooldown = 1.0f;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* MuzzleEffect;

	UPROPERTY()
	USpaceShipCannon* Cannon;

private:
	UPROPERTY()
	UObjectPool* ProjectilePool;

	UPROPERTY()
	UObjectPool* HitEffectPool;

	float Timer;

public:
	UProjectileWeapon();

	virtual void Initialize(USpaceShipCannon* Owner) override;
	virtual void Tick(float DeltaTime) override;
	virtual void Shoot() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
