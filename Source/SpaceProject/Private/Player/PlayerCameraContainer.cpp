// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "PlayerCameraContainer.h"

UPlayerCameraContainer::UPlayerCameraContainer()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

void UPlayerCameraContainer::Attach(USceneComponent* Parent)
{
	Followed = Parent;
}

USceneComponent* UPlayerCameraContainer::GetFollowed() const
{
	return Followed;
}

void UPlayerCameraContainer::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetWorldLocation(Followed->GetComponentLocation());
}
