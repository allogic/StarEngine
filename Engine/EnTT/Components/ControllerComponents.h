#pragma once

namespace StarEngine
{
	struct ShipControllerComponent
	{
		enum ControllerMode : U32
		{
			CONTROLLER_MODE_FIRST_PERSON,
			CONTROLLER_MODE_ORBITAL,
		};

		ControllerMode Mode = CONTROLLER_MODE_FIRST_PERSON;

		R32 KeyboardMovementSpeed = 2.0F;
		R32 MouseMovementSpeed = 2.0F;
		R32 MouseRotationSpeed = 10.0F;
		R32 RollSpeed = 0.1F;

		R32 PositionDrag = 10.0F;
		R32 RotationDrag = 30.0F;
		R32 MouseDrag = 50.0F;

		R32V2 MousePositionStart = { 0.0F, 0.0F };
		R32V2 MousePositionEnd = { 0.0F, 0.0F };

		struct FirstPersonMode
		{
			VOID* Dummy = nullptr;
		};

		FirstPersonMode FirstPerson = {};

		struct OrbitalMode
		{
			R32 Distance = 5.0F;
		};

		OrbitalMode Orbital = {};
	};
}