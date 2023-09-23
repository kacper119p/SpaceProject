#pragma once

#include "SpaceShipController.generated.h"

UINTERFACE()
class USpaceShipController : public UInterface
{
	GENERATED_BODY()
};

class ISpaceShipController
{
	GENERATED_BODY()

public:
	virtual float GetThrust() const = 0;
	virtual FRotator GetRotation() const = 0;
	virtual bool IsShooting() const = 0;
};
