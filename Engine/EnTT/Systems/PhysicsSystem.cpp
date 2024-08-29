#include <Engine/PreCompiled.h>

namespace StarEngine::PhysicsSystem
{
	VOID UpdateVelocities(entt::registry& Registry)
	{
		auto View = Registry.view<TransformComponent, PhysicsComponent>();

		for (auto Entity : View)
		{
			auto& Transform = View.get<TransformComponent>(Entity);
			auto& Physics = View.get<PhysicsComponent>(Entity);

			R32 Epsilon = 1e-6F;

			if (glm::length2(Physics.PositionVelocity) > (Epsilon * Epsilon))
			{
				Transform.LocalPosition += Physics.PositionVelocity;

				Physics.PositionVelocity -= Physics.PositionVelocity * Physics.PositionDrag * Time::GetDeltaTime();

				TransformSystem::ComputeWorldPosition(Registry, Transform);
			}

			// TODO
			//TransformSystem::RecomputeWorldRotation(Registry, Transform);
			//TransformSystem::RecomputeWorldScale(Registry, Transform);
		}
	}
}