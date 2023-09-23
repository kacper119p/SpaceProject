// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "Player/PlayerShip.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "PlayerCameraContainer.h"
#include "PlayerShipController.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip/SpaceShipCannon.h"
#include "SpaceShip/SpaceShipMovement.h"

APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);

	CameraContainerComponent = CreateDefaultSubobject<UPlayerCameraContainer>(TEXT("CameraContainer"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	CameraContainerComponent->Attach(MeshComponent);
	SpringArmComponent->SetupAttachment(CameraContainerComponent);
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	ShipMovementComponent = CreateDefaultSubobject<USpaceShipMovement>(TEXT("MovementComponent"));
	ShipMovementComponent->Attach(MeshComponent);
	
	CameraComponent->bUsePawnControlRotation = false;

	OldCameraRotation = CameraComponent->GetRelativeRotation();
}

USceneComponent* APlayerShip::GetCameraContainer() const
{
	return CameraContainerComponent;
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<USpaceShipCannon>(Cannons);

	for (USpaceShipCannon* Cannon : Cannons)
	{
		Cannon->SetController(CastChecked<APlayerShipController>(Controller));
	}
	
	ShipMovementComponent->SetController(CastChecked<APlayerShipController>(Controller));
}
