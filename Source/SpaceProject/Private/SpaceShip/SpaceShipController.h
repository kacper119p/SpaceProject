#pragma once

class ISpaceShipController
{
public:
	virtual float GetThrust() const = 0;
	virtual FRotator GetRotation() const = 0;
	virtual ~ISpaceShipController() = 0;
};
