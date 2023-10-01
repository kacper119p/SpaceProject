// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RandomRotation.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTILITY_API URandomRotation : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0", ClampMax = "360", UIMin = "0", UIMax = "360"))
	float MinRotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0", ClampMax = "360", UIMin = "0", UIMax = "360"))
	float MaxRotationSpeed;

private:
	FRotator Rotation;

public:
	URandomRotation();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
