// Copyright © Kacper Pastuszka 2023 All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PlayerCameraContainer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEPROJECT_API UPlayerCameraContainer : public USceneComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
	USceneComponent* Followed;
public:
	UPlayerCameraContainer();

public:
	void Attach(USceneComponent* ToFollow);
	USceneComponent* GetFollowed() const;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
