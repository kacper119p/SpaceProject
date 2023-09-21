// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon.generated.h"

class USpaceShipCannon;

UINTERFACE()
class UWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPACEPROJECT_API IWeapon
{
	GENERATED_BODY()

public:
	virtual void Initialize(USpaceShipCannon* Owner) = 0;
	virtual void Tick(float DeltaTime) = 0;
	virtual void Shoot() = 0;
	virtual void BeginPlay() = 0;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) = 0;
};
