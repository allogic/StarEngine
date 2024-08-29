#include <Engine/PreCompiled.h>

namespace StarEngine::TransformSystem
{
	VOID ComputeWorldPosition(entt::registry& Registry, TransformComponent& Transform)
	{
		if (Registry.valid(Transform.ParentEntity))
		{
			auto& ParentTransform = Registry.get<TransformComponent>(Transform.ParentEntity);

			Transform.WorldPosition = ParentTransform.WorldPosition + ParentTransform.WorldRotation * Transform.LocalPosition;
		}
		else
		{
			Transform.WorldPosition = Transform.LocalPosition;
		}
	}

	VOID ComputeWorldRotation(entt::registry& Registry, TransformComponent& Transform)
	{
		if (Registry.valid(Transform.ParentEntity))
		{
			auto& ParentTransform = Registry.get<TransformComponent>(Transform.ParentEntity);

			Transform.WorldRotation = Transform.LocalRotation * ParentTransform.WorldRotation;
		}
		else
		{
			Transform.WorldRotation = Transform.LocalRotation;
		}
	}

	VOID ComputeWorldScale(entt::registry& Registry, TransformComponent& Transform)
	{
		if (Registry.valid(Transform.ParentEntity))
		{
			auto& ParentTransform = Registry.get<TransformComponent>(Transform.ParentEntity);

			Transform.WorldScale = Transform.LocalScale * ParentTransform.WorldScale;
		}
		else
		{
			Transform.WorldScale = Transform.LocalScale;
		}
	}

	R32V3 const& GetWorldPosition(TransformComponent const& Transform)
	{
		return Transform.WorldPosition;
	}

	R32Q const& GetWorldRotation(TransformComponent const& Transform)
	{
		return Transform.WorldRotation;
	}

	R32V3 GetWorldEulerAngles(TransformComponent const& Transform)
	{
		return glm::degrees(glm::eulerAngles(Transform.WorldRotation));
	}

	R32V3 const& GetWorldScale(TransformComponent const& Transform)
	{
		return Transform.WorldScale;
	}

	R32V3 const& GetLocalPosition(TransformComponent const& Transform)
	{
		return Transform.LocalPosition;
	}

	R32Q const& GetLocalRotation(TransformComponent const& Transform)
	{
		return Transform.LocalRotation;
	}

	R32V3 GetLocalEulerAngles(TransformComponent const& Transform)
	{
		return glm::degrees(glm::eulerAngles(Transform.LocalRotation));
	}

	R32V3 const& GetLocalScale(TransformComponent& Transform)
	{
		return Transform.LocalScale;
	}

	VOID SetPosition(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Position)
	{
		Transform.LocalPosition = Position;

		ComputeWorldPosition(Registry, Transform);
	}

	VOID SetRelativePosition(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Position)
	{
		Transform.LocalPosition += Position;

		ComputeWorldPosition(Registry, Transform);
	}

	VOID SetRotation(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Rotation)
	{
		R32V3 EulerAngles = glm::radians(Rotation);

		if (Registry.valid(Transform.ParentEntity))
		{
			auto& ParentTransform = Registry.get<TransformComponent>(Transform.ParentEntity);

			R32Q LocalRotationX = glm::angleAxis(EulerAngles.x, ParentTransform.LocalRight);
			R32Q LocalRotationY = glm::angleAxis(EulerAngles.y, ParentTransform.LocalUp);
			R32Q LocalRotationZ = glm::angleAxis(EulerAngles.z, ParentTransform.LocalForward);

			Transform.LocalRotation = glm::normalize(LocalRotationY * LocalRotationX * LocalRotationZ);

			Transform.LocalRight = glm::normalize(Transform.LocalRotation * ParentTransform.LocalRight);
			Transform.LocalUp = glm::normalize(Transform.LocalRotation * ParentTransform.LocalUp);
			Transform.LocalForward = glm::normalize(Transform.LocalRotation * ParentTransform.LocalForward);
		}
		else
		{
			R32Q LocalRotationX = glm::angleAxis(EulerAngles.x, WORLD_RIGHT);
			R32Q LocalRotationY = glm::angleAxis(EulerAngles.y, WORLD_UP);
			R32Q LocalRotationZ = glm::angleAxis(EulerAngles.z, WORLD_FORWARD);

			Transform.LocalRotation = glm::normalize(LocalRotationY * LocalRotationX * LocalRotationZ);

			Transform.LocalRight = glm::normalize(Transform.LocalRotation * WORLD_RIGHT);
			Transform.LocalUp = glm::normalize(Transform.LocalRotation * WORLD_UP);
			Transform.LocalForward = glm::normalize(Transform.LocalRotation * WORLD_FORWARD);
		}

		ComputeWorldRotation(Registry, Transform);
		ComputeWorldPosition(Registry, Transform);
	}

	VOID SetRelativeRotation(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Rotation)
	{
		R32V3 EulerAngles = glm::radians(Rotation);

		if (Registry.valid(Transform.ParentEntity))
		{
			auto& ParentTransform = Registry.get<TransformComponent>(Transform.ParentEntity);

			R32Q LocalRotationX = glm::angleAxis(EulerAngles.x, ParentTransform.LocalRight);
			R32Q LocalRotationY = glm::angleAxis(EulerAngles.y, ParentTransform.LocalUp);
			R32Q LocalRotationZ = glm::angleAxis(EulerAngles.z, ParentTransform.LocalForward);

			Transform.LocalRotation = Transform.LocalRotation * glm::normalize(LocalRotationY * LocalRotationX * LocalRotationZ);

			Transform.LocalRight = glm::normalize(Transform.LocalRotation * ParentTransform.LocalRight);
			Transform.LocalUp = glm::normalize(Transform.LocalRotation * ParentTransform.LocalUp);
			Transform.LocalForward = glm::normalize(Transform.LocalRotation * ParentTransform.LocalForward);
		}
		else
		{
			R32Q LocalRotationX = glm::angleAxis(EulerAngles.x, WORLD_RIGHT);
			R32Q LocalRotationY = glm::angleAxis(EulerAngles.y, WORLD_UP);
			R32Q LocalRotationZ = glm::angleAxis(EulerAngles.z, WORLD_FORWARD);

			Transform.LocalRotation = Transform.LocalRotation * glm::normalize(LocalRotationY * LocalRotationX * LocalRotationZ);

			Transform.LocalRight = glm::normalize(Transform.LocalRotation * WORLD_RIGHT);
			Transform.LocalUp = glm::normalize(Transform.LocalRotation * WORLD_UP);
			Transform.LocalForward = glm::normalize(Transform.LocalRotation * WORLD_FORWARD);
		}

		ComputeWorldRotation(Registry, Transform);
		ComputeWorldPosition(Registry, Transform);
	}

	VOID SetScale(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Scale)
	{
		Transform.LocalScale = Scale;

		ComputeWorldScale(Registry, Transform);
	}

	VOID SetRelativeScale(entt::registry& Registry, TransformComponent& Transform, R32V3 const& Scale)
	{
		Transform.LocalScale += Scale;

		ComputeWorldScale(Registry, Transform);
	}
}