#include <Engine/PreCompiled.h>
#include <Engine/Model.h>

#include <Engine/GLAD/glad.h>

#include <Engine/GLFW/glfw3.h>

#include <Engine/OpenGL/Gizmo.h>

#include <Engine/OpenGL/Renderer/Renderer.h>

#include <Engine/OpenGL/VertexArray/PrimitiveVertexArrays.h>

/*
 * TODO:
 *  - Model Loading
 *  - Profiler
 *  - Fast ECS with Sparse/Dense Sets
 *  - Quadric Error Metrics Mesh Simplification which also supports instanced meshes
 *  - GPU Culling System which also supports instanced meshes
 *  - Warp Drive Shader
 *  - HDR Bloom
 *  - Asteroid Field Generator
 *  - Global Volumetric Fog
 *  - Audio System
 *  - Sexy planets with Rings and shadows
 *  - Font Rendering
 *  - Validate if input PBR textures have sRGB or linear color spaces
 */

/*
 * ARTSTYLE:
 *  - Falling Frontier
 *  - Homeworld
 *  - Limit Theory
 *  - House Of The Dying Sun
 */

using namespace StarEngine;

static U32 m_OpenGLMajorVersion = 4;
static U32 m_OpenGLMinorVersion = 6;

static CHAR m_WindowTitle[] = "Star Engine";
static U32 m_WindowWidth = 1920;
static U32 m_WindowHeight = 1080;
static U32 m_WindowAntiAliasing = 8;

static R32 m_AspectRatio = (R32)m_WindowWidth / m_WindowHeight;

static R32 m_PrevTimeHotLoad = 0.0F;

#ifdef SE_DEBUG

static VOID GLDebugCallback(U32 Source, U32 Type, U32 Id, U32 Severity, I32 Length, CHAR const* Message, VOID const* UserParam);

#endif // SE_DEBUG

static VOID WindowResizeCallback(GLFWwindow* Context, I32 Width, I32 Height);
static VOID CursorPositionCallback(GLFWwindow* Context, R64 X, R64 Y);
static VOID MouseButtonCallback(GLFWwindow* Context, I32 Button, I32 Action, I32 Mods);
static VOID ScrollCallback(GLFWwindow* Context, R64 X, R64 Y);
static VOID KeyCallback(GLFWwindow* Context, I32 Key, I32 ScanCode, I32 Action, I32 Mods);

I32 main(I32 Argc, CHAR** Argv)
{
	if (glfwInit())
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_OpenGLMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_OpenGLMinorVersion);
		glfwWindowHint(GLFW_SAMPLES, m_WindowAntiAliasing);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);

		GLFWwindow* Context = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowTitle, 0, 0);

		if (Context)
		{
			glfwMakeContextCurrent(Context);
			glfwSwapInterval(0);

			I32 GLVersion = gladLoadGL();

			if (GLVersion > 0)
			{
				glEnable(GL_DEBUG_OUTPUT);

				glDebugMessageCallback(GLDebugCallback, 0);

				AssetLoader::Create("C:\\Users\\mialb\\Downloads\\StarEngine\\Assets");

				PrimitiveVertexArrays::Create();

				Gizmo::Create();
				Renderer::Create(m_WindowWidth, m_WindowHeight);

				entt::registry Registry = {};

				{
					entt::entity PlayerEntity = Registry.create();

					Registry.emplace<TransformComponent>(PlayerEntity);
					Registry.emplace<PhysicsComponent>(PlayerEntity);
					Registry.emplace<ShipControllerComponent>(PlayerEntity);
					Registry.emplace<CameraComponent>(PlayerEntity);
					auto& PointLight = Registry.emplace<PointLightComponent>(PlayerEntity);

					PointLight.Intensity = 1.0F;
					PointLight.Radius = 10.0F;
					PointLight.Color = R32V3{ 1.0F, 1.0F, 1.0F };
				}

				{
					entt::entity TestEntity = Registry.create();
					
					auto& Transform = Registry.emplace<TransformComponent>(TestEntity);
					auto& PointLight = Registry.emplace<PointLightComponent>(TestEntity);
					
					TransformSystem::SetPosition(Registry, Transform, R32V3{ 0.0F, 1.0F, 0.0F });
					
					PointLight.Intensity = 1.0F;
					PointLight.Radius = 10.0F;
					PointLight.Color = R32V3{ 1.0F, 0.15F, 0.0F };
				}

				{
					//entt::entity CockpitEntity = ModelRegistry::GetModelByName("Cockpit")->CreateEntity(Registry);
				}

				glfwSetWindowSizeCallback(Context, WindowResizeCallback);
				glfwSetCursorPosCallback(Context, CursorPositionCallback);
				glfwSetMouseButtonCallback(Context, MouseButtonCallback);
				glfwSetScrollCallback(Context, ScrollCallback);
				glfwSetKeyCallback(Context, KeyCallback);

				while (!glfwWindowShouldClose(Context))
				{
					Time::Update();
					Event::Update(Context);

					if ((Time::GetTime() - m_PrevTimeHotLoad) > 1.0F)
					{
						m_PrevTimeHotLoad = Time::GetTime();

						AssetLoader::Update();
					}

					ControllerSystem::UpdateInputs(Registry);
					PhysicsSystem::UpdateVelocities(Registry);

					Renderer::Draw(Registry, m_AspectRatio);

					glfwSwapBuffers(Context);
				}

				Renderer::Destroy();
				Gizmo::Destroy();

				PrimitiveVertexArrays::Destroy();

				AssetLoader::Destroy();
			}
			else
			{
				std::printf("Failed loading GL\n");
			}

			glfwDestroyWindow(Context);
			glfwTerminate();
		}
		else
		{
			std::printf("Failed creating window\n");
		}
	}
	else
	{
		std::printf("Failed initializing GLFW\n");
	}

#ifdef SE_DEBUG

	Memory::CheckForLeaks();

#endif // SE_DEBUG

	return 0;
}

#ifdef SE_DEBUG

static VOID GLDebugCallback(U32 Source, U32 Type, U32 Id, U32 Severity, I32 Length, CHAR const* Message, VOID const* UserParam)
{
	switch (Severity)
	{
		case GL_DEBUG_SEVERITY_NOTIFICATION: break;
		case GL_DEBUG_SEVERITY_LOW: std::printf("[GL] Severity:Low Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_MEDIUM: std::printf("[GL] Severity:Medium Type:0x%x Message:%s\n", Type, Message); break;
		case GL_DEBUG_SEVERITY_HIGH: std::printf("[GL] Severity:High Type:0x%x Message:%s\n", Type, Message); break;
	}
}

#endif // SE_DEBUG

static VOID WindowResizeCallback(GLFWwindow* Context, I32 Width, I32 Height)
{
	m_WindowWidth = (U32)Width;
	m_WindowHeight = (U32)Height;
	m_AspectRatio = (R32)m_WindowWidth / m_WindowHeight;

	glViewport(0, 0, m_WindowWidth, m_WindowHeight);

	Renderer::Resize(m_WindowWidth, m_WindowHeight);
}

static VOID CursorPositionCallback(GLFWwindow* Context, R64 X, R64 Y)
{
	Event::SetMouseX((R32)X);
	Event::SetMouseY((R32)Y);
}

static VOID MouseButtonCallback(GLFWwindow* Context, I32 Button, I32 Action, I32 Mods)
{

}

static VOID ScrollCallback(GLFWwindow* Context, R64 X, R64 Y)
{

}

static VOID KeyCallback(GLFWwindow* Context, I32 Key, I32 ScanCode, I32 Action, I32 Mods)
{
	
}