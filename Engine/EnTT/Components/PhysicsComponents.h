#pragma once

namespace StarEngine
{
	struct PhysicsComponent
	{
		R32V3 PositionVelocity = { 0.0F, 0.0F, 0.0F };
		R32V3 RotationVelocity = { 0.0F, 0.0F, 0.0F };

		R32 PositionDrag = 1.0F;
		R32 RotationDrag = 1.0F;
	};
}