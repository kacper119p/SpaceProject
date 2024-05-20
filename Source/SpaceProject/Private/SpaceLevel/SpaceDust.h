// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "Movement/FollowPlayerComponent.h"
#include "SpaceDust.generated.h"

UCLASS()
class SPACEPROJECT_API ASpaceDust : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere)
	UFollowPlayerComponent* FollowPlayerComponent;

public:
	ASpaceDust();
};
