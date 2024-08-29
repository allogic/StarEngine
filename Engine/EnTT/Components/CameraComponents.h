#pragma once

namespace StarEngine
{
	struct CameraComponent
	{
		enum CameraMode : U32
		{
			CAMERA_MODE_PERSPECTIVE,
			CAMERA_MODE_ORTHOGRAPHIC,
		};

		CameraMode Mode = CAMERA_MODE_PERSPECTIVE;

		R32 NearPlane = 0.001F;
		R32 FarPlane = 100000.0F;

		struct PerspectiveMode
		{
			R32 FieldOfView = 45.0F;
		};

		PerspectiveMode Perspective = {};

		struct OrthographicMode
		{
			R32 Left = -1.0F;
			R32 Right = 1.0F;
			R32 Top = 1.0F;
			R32 Bottom = -1.0F;
		};

		OrthographicMode Orthographic = {};
	};
}