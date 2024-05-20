// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowPlayerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTILITY_API UFollowPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FVector Offset;

	UPROPERTY()
	TSoftObjectPtr<AActor> Player;

public:
	UFollowPlayerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent
	(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
