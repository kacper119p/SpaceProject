// Copyright © Kacper Pastuszka 2023 All rights reserved.


#include "Movement/FollowPlayerComponent.h"

#include "Kismet/GameplayStatics.h"


UFollowPlayerComponent::UFollowPlayerComponent()
{
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
	PrimaryComponentTick.bCanEverTick = true;
}


void UFollowPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void UFollowPlayerComponent
::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Player.IsValid())
	{
		return;
	}

	GetOwner()->SetActorLocation(Player->GetActorLocation() + Offset);
}
