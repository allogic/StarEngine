#pragma once

namespace StarEngine::TransformSystem
{
	VOID ComputeWorldPosition(entt::registry& Registry, TransformComponent& Transform);
	VOID ComputeWorldRotation(entt::registry& Registry, TransformComponent& Transform);
	VOID ComputeWorldScale(entt::registry& Registry, TransformComponent& Transform);

	R32V3 const& GetWorldPosition(TransformComponent const& Transform);
	R32Q const& GetWorldRotation(TransformComponent const& Transform);
	R32V3 GetWorldEulerAngles(TransformComponent const& Transform);
	R32V3 const& GetWorldScale(TransformComponent const& Transform);

	R32V3 const& GetLocalPosition(TransformComponent const& Transform);
	R32Q const& GetLocalRotation(TransformComponent const& Transform);
	R32V3 GetLocalEulerAngles(TransformComponent const& Transform);
	R32V3 const& GetLocalScale(TransformComponent const& Transform);

	VOID SetPosition(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Position);
	VOID SetRelativePosition(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Position);

	VOID SetRotation(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Rotation);
	VOID SetRelativeRotation(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Rotation);

	VOID SetScale(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Scale);
	VOID SetRelativeScale(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Scale);
}