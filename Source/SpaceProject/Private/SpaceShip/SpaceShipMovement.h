// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceShipMovement.generated.h"

class USpaceShipController;
class ISpaceShipController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEPROJECT_API USpaceShipMovement : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Control")
	UPrimitiveComponent* Controlled;

	UPROPERTY(EditAnywhere, Category = "Control")
	TScriptInterface<ISpaceShipController> Controller;

	UPROPERTY(EditAnywhere, Category = "Movement Characteristics")
	double MaxThrust = 1000.0;

	UPROPERTY(EditAnywhere, Category = "Movement Characteristics")
	double MaxRotationSpeed = 4.0;

public:
	USpaceShipMovement();

protected:
	virtual void BeginPlay() override;

public:
	void Attach(UPrimitiveComponent* InControlled);
	void SetController(ISpaceShipController* InController);

	virtual void TickComponent
	(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void HandleThrust(float Thrust);
	void HandleRotation(const FRotator& Rotation, float DeltaTime);
};
