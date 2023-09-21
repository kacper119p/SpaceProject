// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceShipCannon.generated.h"

class IWeapon;
class UWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEPROJECT_API USpaceShipCannon : public USceneComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Weapons", meta = (MustImplement = Weapon))
	UClass* Weapon;

private:
	UPROPERTY()
	TScriptInterface<IWeapon> WeaponInstance;

public:
	USpaceShipCannon();

	void Shoot();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
