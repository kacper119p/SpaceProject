// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "Player/PlayerShip.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputAction.h"
#include "VectorTypes.h"


APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	CameraContainerComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CameraContainer"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	MeshComponent->SetupAttachment(RootComponent);
	CameraContainerComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(CameraContainerComponent);
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(false);

	MoveDirection = FVector::Zero();
}

void APlayerShip::OnMove(const FInputActionValue& Value)
{
	const FVector2d Input = Value.Get<FVector2d>();
	const FVector2d Direction = Input.GetSafeNormal();
	MoveDirection = FVector(Direction.X, Direction.Y, 0);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
	                                 FString::Printf(TEXT("Input: %lf %lf"), Direction.X, Direction.Y));
}

void APlayerShip::OnMouseMove(const FInputActionValue& Value)
{
	const FVector2d Input = Value.Get<FVector2d>();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald,
	                                 FString::Printf(TEXT("Input: %lf %lf"), Input.X, Input.Y));
	
	CameraContainerComponent->AddLocalRotation(FRotator(Input.Y, Input.X, 0.0));
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
}

void APlayerShip::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector CrossForward
		= UE::Geometry::Cross(MeshComponent->GetForwardVector(), CameraComponent->GetForwardVector());
	const FVector CrossUp
		= UE::Geometry::Cross(MeshComponent->GetUpVector(), CameraComponent->GetUpVector());

	if (CrossUp.Length() > 0.1f || CrossForward.Length() > 0.1f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow,
		                                 FString::Printf(
			                                 TEXT("Rotate: %lf %lf"), CrossForward.Length(),
			                                 CrossUp.Length()));
		FRotator Rotator
			= FRotator(FQuat(CrossForward, 3.14 * DeltaTime));
		Rotator
			+= FRotator(FQuat(CrossUp, 3.14 * DeltaTime));

		MeshComponent->AddWorldRotation(Rotator);
	}

	const FVector MoveDirectionWorld
		= MeshComponent->GetComponentTransform()
		               .TransformVector(MoveDirection)
		               .GetSafeNormal();

	MeshComponent->AddForce(MoveDirectionWorld * 1000.0, NAME_None, true);
	
	CameraContainerComponent->SetWorldLocation(MeshComponent->GetComponentTransform().GetLocation());
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerShip::OnMove);
		EnhancedInputComponent->BindAction(MouseMoveAction, ETriggerEvent::Triggered, this, &APlayerShip::OnMouseMove);
	}
}

void APlayerShip::PawnClientRestart()
{
	Super::PawnClientRestart();
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem
			<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}
