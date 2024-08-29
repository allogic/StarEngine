#pragma once

namespace StarEngine
{
	struct AmbientLight
	{
		R32 Intensity;
	};

	struct DirectionLight
	{
		R32 Intensity;
	};

	struct PointLight
	{
		R32V3 Position;
		R32 Intensity;
		R32V3 Color;
		R32 Radius;
	};

	struct SpotLight
	{
		R32 Intensity;
	};

	struct AreaLight
	{
		R32 Intensity;
	};
}