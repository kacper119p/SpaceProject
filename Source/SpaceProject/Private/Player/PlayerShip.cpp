// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "Player/PlayerShip.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PrimitiveComponent.h"


APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerRootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	MovementComponent = CreateDefaultSubobject<UMovementComponent>(TEXT("MovementComponent"));

	MeshComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetupAttachment(MeshComponent);
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	MoveDirection = FVector::Zero();
}

void APlayerShip::Move(const FInputActionValue& Value)
{
	const FVector2d Input = Value.Get<FVector2d>();
	const FVector2d Direction = Input.GetSafeNormal();
	MoveDirection = FVector(Direction.X, Direction.Y, 0);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Emerald, FString::Printf(TEXT("input: %lf %lf"), Direction.X, Direction.Y));
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
}

void APlayerShip::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	MeshComponent->AddForce(MoveDirection * 1000.0, NAME_None, true);
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerShip::Move);
	}
}

void APlayerShip::PawnClientRestart()
{
	Super::PawnClientRestart();
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}
