// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "ObjectPooling/ObjectPoolComponent.h"
#include "ObjectPooling/PooledActor.h"

UObjectPoolComponent::UObjectPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UObjectPoolComponent::Initialize(APooledActor* Template, const int32 Size)
{
	Members.Reserve(Size);
	Stack.Reserve(Size);

	FActorSpawnParameters Params;
	Params.Template = Template;

	for (int32 i = 0; i < Size; i++)
	{
		APooledActor* Created
			= Cast<APooledActor>(GetWorld()->SpawnActor(Template->GetClass(), nullptr, nullptr, Params));
		Members.Push(Created);
		Stack.Push(Created);
	}
}

APooledActor* UObjectPoolComponent::Pull(const FVector& Location,const FRotator& Rotation)
{
	APooledActor* Pulled = Stack.Pop();
	Pulled->SetActorLocationAndRotation(Location, Rotation);
	return Pulled;
}

void UObjectPoolComponent::Return(APooledActor* const Object)
{
	Stack.Push(Object);
}

void UObjectPoolComponent::Dispose()
{
	for (APooledActor* Member : Members)
	{
		Member->Destroy();
	}
}
