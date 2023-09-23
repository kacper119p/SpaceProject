// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

class UObjectPool;

UCLASS()
class UTILITY_API APooledActor : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnabledSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisabledSignature);

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnabledSignature OnEnabledEvent;

	UPROPERTY(BlueprintAssignable)
	FOnDisabledSignature OnDisabledEvent;

protected:
	UPROPERTY()
	UObjectPool* ObjectPool;

private:
	bool bIsActive;

public:
	APooledActor();

	virtual void Initialize(UObjectPool* InPool);
	void Enable();
	void Disable();
	void SetActive(bool bActive);
	bool IsActive() const;
	void Return();
};
