// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPooling/PooledActor.h"
#include "HitEffect.generated.h"

UCLASS()
class SPACEPROJECT_API AHitEffect : public APooledActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	float Lifespan;
	
private:
	float Timer;

public:
	AHitEffect();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void OnObjectEnabled();
};
