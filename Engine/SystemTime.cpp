#include <Engine/PreCompiled.h>

#include <Engine/GLFW/glfw3.h>

namespace StarEngine::Time
{
	static R32 m_Time = 0.0F;
	static R32 m_TimeDelta = 0.0F;
	static R32 m_TimePrev = 0.0F;

	VOID Update()
	{
		m_Time = (R32)glfwGetTime();
		m_TimeDelta = m_Time - m_TimePrev;
		m_TimePrev = m_Time;
	}

	R32 GetTime()
	{
		return m_Time;
	}

	R32 GetDeltaTime()
	{
		return m_TimeDelta;
	}
}