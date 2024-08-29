#pragma once

namespace StarEngine
{
	struct TransformComponent
	{
		entt::entity ParentEntity = entt::null;

		R32V3 LocalRight = { 1.0F, 0.0F, 0.0F };
		R32V3 LocalUp = { 0.0F, 1.0F, 0.0F };
		R32V3 LocalForward = { 0.0F, 0.0F, 1.0F };

		R32V3 LocalPosition = { 0.0F, 0.0F, 0.0F };
		R32Q LocalRotation = { 1.0F, 0.0F, 0.0F, 0.0F };
		R32V3 LocalScale = { 1.0F, 1.0F, 1.0F };

		R32V3 WorldPosition = { 0.0F, 0.0F, 0.0F };
		R32Q WorldRotation = { 1.0F, 0.0F, 0.0F, 0.0F };
		R32V3 WorldScale = { 1.0F, 1.0F, 1.0F };
	};
}