// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool.generated.h"

class APooledActor;

UCLASS()
class UTILITY_API UObjectPool : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<APooledActor*> Members;
	UPROPERTY()
	TArray<APooledActor*> Stack;

public:
	UObjectPool();
	
	TArray<APooledActor*> GetMembers() const;
	
	void Initialize(const TSubclassOf<APooledActor> Template, int32 Size);
	void Dispose();
	
	APooledActor* Pull(const FVector& Location,const FRotator& Rotation);
	void Return(APooledActor* const Object);
};
