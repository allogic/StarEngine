#include <Engine/PreCompiled.h>

#include <Engine/GLFW/glfw3.h>

namespace StarEngine::Event
{
	enum EventState : U8
	{
		EVENT_STATE_NONE,
		EVENT_STATE_DOWN,
		EVENT_STATE_HELD,
		EVENT_STATE_UP,
	};

	struct EventRecord
	{
		EventState Curr;
		EventState Prev;
	};

	static EventRecord m_KeyboardKeys[348] = {};
	static EventRecord m_MouseKeys[7] = {};

	static R32 m_MouseX = 0.0F;
	static R32 m_MouseY = 0.0F;

	VOID Update(GLFWwindow* Context)
	{
		glfwPollEvents();

		for (U32 Key = GLFW_KEY_SPACE; Key < GLFW_KEY_LAST; Key++)
		{
			EventState& Curr = m_KeyboardKeys[Key].Curr;
			EventState& Prev = m_KeyboardKeys[Key].Prev;

			Prev = Curr;

			I32 Action = glfwGetKey(Context, Key);

			switch (Action)
			{
				case GLFW_PRESS: Curr = ((Curr != EVENT_STATE_DOWN) && (Prev != EVENT_STATE_HELD)) ? EVENT_STATE_DOWN : EVENT_STATE_HELD; break;
				case GLFW_RELEASE: Curr = ((Curr != EVENT_STATE_UP) && (Prev == EVENT_STATE_HELD)) ? EVENT_STATE_UP : EVENT_STATE_NONE; break;
			}
		}

		for (U32 Key = 0; Key < GLFW_MOUSE_BUTTON_LAST; Key++)
		{
			EventState& Curr = m_MouseKeys[Key].Curr;
			EventState& Prev = m_MouseKeys[Key].Prev;

			Prev = Curr;

			I32 Action = glfwGetMouseButton(Context, Key);

			switch (Action)
			{
				case GLFW_PRESS: Curr = ((Curr != EVENT_STATE_DOWN) && (Prev != EVENT_STATE_HELD)) ? EVENT_STATE_DOWN : EVENT_STATE_HELD; break;
				case GLFW_RELEASE: Curr = ((Curr != EVENT_STATE_UP) && (Prev == EVENT_STATE_HELD)) ? EVENT_STATE_UP : EVENT_STATE_NONE; break;
			}
		}
	}

	BOOL KeyDown(KeyboardKey Key)
	{
		return m_KeyboardKeys[Key].Curr == EVENT_STATE_DOWN;
	}

	BOOL KeyHeld(KeyboardKey Key)
	{
		return m_KeyboardKeys[Key].Curr == EVENT_STATE_HELD;
	}

	BOOL KeyUp(KeyboardKey Key)
	{
		return m_KeyboardKeys[Key].Curr == EVENT_STATE_UP;
	}

	BOOL MouseDown(MouseKey Key)
	{
		return m_MouseKeys[Key].Curr == EVENT_STATE_DOWN;
	}

	BOOL MouseHeld(MouseKey Key)
	{
		return m_MouseKeys[Key].Curr == EVENT_STATE_HELD;
	}

	BOOL MouseUp(MouseKey Key)
	{
		return m_MouseKeys[Key].Curr == EVENT_STATE_UP;
	}

	R32 GetMouseX()
	{
		return m_MouseX;
	}

	R32 GetMouseY()
	{
		return m_MouseY;
	}

	R32V2 GetMousePosition()
	{
		return { m_MouseX, m_MouseY };
	}

	VOID SetMouseX(R32 X)
	{
		m_MouseX = X;
	}

	VOID SetMouseY(R32 Y)
	{
		m_MouseY = Y;
	}
}