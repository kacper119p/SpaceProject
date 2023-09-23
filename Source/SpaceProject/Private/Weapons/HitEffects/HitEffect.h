// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPooling/PooledActor.h"
#include "HitEffect.generated.h"

class UNiagaraComponent;

UCLASS()
class SPACEPROJECT_API AHitEffect : public APooledActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Life Cycle")
	float LifeTime = 0;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* NiagaraComponent;
	
private:
	float Timer = 0;

public:
	AHitEffect();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnObjectEnabled();
};
