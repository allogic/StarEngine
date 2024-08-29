#pragma once

namespace StarEngine
{
	struct AmbientLightComponent
	{
		R32 Intensity;
	};

	struct DirectionLightComponent
	{
		R32 Intensity;
	};

	struct PointLightComponent
	{
		R32 Intensity;
		R32 Radius;

		R32V3 Color;
	};

	struct SpotLightComponent
	{
		R32 Intensity;
	};

	struct AreaLightComponent
	{
		R32 Intensity;
	};
}