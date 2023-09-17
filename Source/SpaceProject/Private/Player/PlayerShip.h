// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once
#include "InputActionValue.h"

#include "PlayerShip.generated.h"

class USpaceShipMovement;
class UPlayerCameraContainer;
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
private:
	FRotator OldCameraRotation;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	UPlayerCameraContainer* CameraContainerComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
	USpaceShipMovement* ShipMovementComponent;

public:
	APlayerShip();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	USceneComponent* GetCameraContainer() const;
};
