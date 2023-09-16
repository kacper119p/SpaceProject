// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once
#include "InputActionValue.h"

#include "PlayerShip.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputComponent;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class UPhysicsConstraintComponent;

UCLASS()
class APlayerShip : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* CameraContainerComponent;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

public:
	APlayerShip();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	USceneComponent* GetCameraContainer() const;
};
