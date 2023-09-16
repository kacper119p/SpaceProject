// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "Player/PlayerShip.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "PlayerShipController.h"
#include "GameFramework/Pawn.h"

APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	CameraContainerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CameraContainer"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	
	CameraContainerComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(CameraContainerComponent);
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
}

void APlayerShip::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	const APlayerShipController* PlayerController = Cast<APlayerShipController>(Controller);
	check(PlayerController);
	
	MeshComponent->AddWorldRotation(PlayerController->GetRotation());
	
	
	const FVector MoveDirectionWorld
		= GetTransform()
		               .TransformVector(FVector(PlayerController->GetThrust(), 0, 0))
		               .GetSafeNormal();
	
	MeshComponent->AddForce(MoveDirectionWorld * 1000.0, NAME_None, true);
	
	CameraContainerComponent->SetWorldLocation(MeshComponent->GetComponentTransform().GetLocation());
}

USceneComponent* APlayerShip::GetCameraContainer() const
{
	return CameraContainerComponent;
}
