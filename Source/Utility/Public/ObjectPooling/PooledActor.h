// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS()
class UTILITY_API APooledActor : public AActor
{
	GENERATED_BODY()
	
private:
	bool bIsActive;
	
public:
	APooledActor();
	
	void Enable();
	void Disable();
	void SetActive(bool bActive);
	bool IsActive() const;
};
