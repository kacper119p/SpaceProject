// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"

class APooledActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTILITY_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<APooledActor*> Members;
	TArray<APooledActor*> Stack;

public:
	UObjectPoolComponent();
	
	void Initialize(APooledActor* Template, int32 Size);
	void Dispose();
	
	APooledActor* Pull(const FVector& Location,const FRotator& Rotation);
	void Return(APooledActor* const Object);
};
