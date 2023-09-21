// Copyright © Kacper Pastuszka 2023 All rights reserved.

#include "ObjectPooling/ObjectPool.h"
#include "ObjectPooling/PooledActor.h"

UObjectPool::UObjectPool()
{
}

TArray<APooledActor*> UObjectPool::GetMembers() const
{
	return Members;
}

void UObjectPool::Initialize(const TSubclassOf<APooledActor> Template, const int32 Size)
{
	Members.Reserve(Size);
	Stack.Reserve(Size);

	for (int32 i = 0; i < Size; i++)
	{
		UWorld* World = GetWorld();
		check(World);
		AActor* Actor = World->SpawnActor(Template.Get());
		APooledActor* Created = CastChecked<APooledActor>(Actor);
		Created->Initialize(this);
		Members.Push(Created);
		Stack.Push(Created);
	}
}

void UObjectPool::Dispose()
{
	for (APooledActor* Member : Members)
	{
		Member->Destroy();
	}
}

APooledActor* UObjectPool::Pull(const FVector& Location, const FRotator& Rotation)
{
	APooledActor* Pulled = Stack.Pop();
	Pulled->SetActorLocationAndRotation(Location, Rotation);
	return Pulled;
}

void UObjectPool::Return(APooledActor* const Object)
{
	Stack.Push(Object);
}
