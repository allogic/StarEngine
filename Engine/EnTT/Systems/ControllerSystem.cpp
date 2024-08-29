#include <Engine/PreCompiled.h>

namespace StarEngine::ControllerSystem
{
	static VOID HandlePosition(entt::registry& Registry, TransformComponent& Transform, PhysicsComponent& Physics, ShipControllerComponent& Controller);
	static VOID HandleRotation(entt::registry& Registry, TransformComponent& Transform, PhysicsComponent& Physics, ShipControllerComponent& Controller);

	VOID UpdateInputs(entt::registry& Registry)
	{
		auto View = Registry.view<TransformComponent, PhysicsComponent, ShipControllerComponent>();

		for (auto Entity : View)
		{
			auto& Transform = View.get<TransformComponent>(Entity);
			auto& Physics = View.get<PhysicsComponent>(Entity);
			auto& Controller = View.get<ShipControllerComponent>(Entity);

			// TODO
			Physics.PositionDrag = Controller.PositionDrag;
			Physics.RotationDrag = Controller.RotationDrag;

			HandlePosition(Registry, Transform, Physics, Controller);
			HandleRotation(Registry, Transform, Physics, Controller);
		}
	}

	static VOID HandlePosition(entt::registry& Registry, TransformComponent& Transform, PhysicsComponent& Physics, ShipControllerComponent& Controller)
	{
		if (Event::KeyHeld(Event::KEYBOARD_KEY_D)) TransformSystem::SetRelativePosition(Registry, Transform, Transform.LocalRight * Controller.KeyboardMovementSpeed * Time::GetDeltaTime());
		if (Event::KeyHeld(Event::KEYBOARD_KEY_A)) TransformSystem::SetRelativePosition(Registry, Transform, -Transform.LocalRight * Controller.KeyboardMovementSpeed * Time::GetDeltaTime());

		if (Event::KeyHeld(Event::KEYBOARD_KEY_W)) TransformSystem::SetRelativePosition(Registry, Transform, -Transform.LocalForward * Controller.KeyboardMovementSpeed * Time::GetDeltaTime());
		if (Event::KeyHeld(Event::KEYBOARD_KEY_S)) TransformSystem::SetRelativePosition(Registry, Transform, Transform.LocalForward * Controller.KeyboardMovementSpeed * Time::GetDeltaTime());
	}

	static VOID HandleRotation(entt::registry& Registry, TransformComponent& Transform, PhysicsComponent& Physics, ShipControllerComponent& Controller)
	{
		if (Event::KeyHeld(Event::KEYBOARD_KEY_E)) TransformSystem::SetRelativeRotation(Registry, Transform, R32V3{ 0.0F, 0.0F, -Controller.RollSpeed });
		if (Event::KeyHeld(Event::KEYBOARD_KEY_Q)) TransformSystem::SetRelativeRotation(Registry, Transform, R32V3{ 0.0F, 0.0F, Controller.RollSpeed });

		if (Event::MouseDown(Event::MOUSE_KEY_RIGHT))
		{
			Controller.MousePositionStart = Event::GetMousePosition();
		}

		if (Event::MouseHeld(Event::MOUSE_KEY_RIGHT))
		{
			Controller.MousePositionEnd = Event::GetMousePosition();

			R32V2 MousePositionDelta = Controller.MousePositionStart - Controller.MousePositionEnd;
			R32 Epsilon = 1e-2F;

			if (glm::length2(MousePositionDelta) > (Epsilon * Epsilon))
			{
				Controller.MousePositionStart -= MousePositionDelta * Controller.MouseDrag * Time::GetDeltaTime();
			}
			else
			{
				Controller.MousePositionStart = Controller.MousePositionEnd;
			}

			R32 Pitch = MousePositionDelta.y * Controller.MouseRotationSpeed * Time::GetDeltaTime();
			R32 Yaw = MousePositionDelta.x * Controller.MouseRotationSpeed * Time::GetDeltaTime();

			TransformSystem::SetRelativeRotation(Registry, Transform, R32V3{ Pitch, Yaw, 0.0F });
		}
	}
}