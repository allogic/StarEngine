#include <Engine/PreCompiled.h>

#include <Engine/OpenGL/Shader/Shader.h>
#include <Engine/OpenGL/Shader/ShaderRegistry.h>

namespace StarEngine::ShaderRegistry
{
	static std::map<std::string, Shader*> m_Shaders = {};

	VOID Create(fs::path const& ShaderFilePath)
	{
		Shader* DeferredGeometry = AddShader("PrincipledBRDF/DeferredGeometry");
		Shader* DeferredLighting = AddShader("PrincipledBRDF/DeferredLighting");

		Shader* PassThrough = AddShader("PostProcess/PassThrough");

		Shader* GizmoLine = AddShader("Gizmo/Line");
		Shader* GizmoQuad = AddShader("Gizmo/Quad");

		Shader* GizmoLineBatch = AddShader("Gizmo/LineBatch");
		Shader* GizmoQuadBatch = AddShader("Gizmo/QuadBatch");

		Shader* SkyBox = AddShader("SkyBox/Default");

		DeferredGeometry->Load(ShaderFilePath / "PrincipledBRDF" / "DeferredGeometryVertexShader.glsl", ShaderFilePath / "PrincipledBRDF" / "DeferredGeometryFragmentShader.glsl");
		DeferredLighting->Load(ShaderFilePath / "PrincipledBRDF" / "DeferredLightingVertexShader.glsl", ShaderFilePath / "PrincipledBRDF" / "DeferredLightingFragmentShader.glsl");

		PassThrough->Load(ShaderFilePath / "PostProcess" / "VertexShader.glsl", ShaderFilePath / "PostProcess" / "FragmentShader.glsl");

		GizmoLine->Load(ShaderFilePath / "Gizmo" / "Line" / "VertexShader.glsl", ShaderFilePath / "Gizmo" / "Line" / "FragmentShader.glsl");
		GizmoQuad->Load(ShaderFilePath / "Gizmo" / "Quad" / "VertexShader.glsl", ShaderFilePath / "Gizmo" / "Quad" / "FragmentShader.glsl");

		GizmoLineBatch->Load(ShaderFilePath / "Gizmo" / "LineBatch" / "VertexShader.glsl", ShaderFilePath / "Gizmo" / "LineBatch" / "FragmentShader.glsl");
		GizmoQuadBatch->Load(ShaderFilePath / "Gizmo" / "QuadBatch" / "VertexShader.glsl", ShaderFilePath / "Gizmo" / "QuadBatch" / "FragmentShader.glsl");

		SkyBox->Load(ShaderFilePath / "SkyBox" / "Default" / "VertexShader.glsl", ShaderFilePath / "SkyBox" / "Default" / "FragmentShader.glsl");
	}

	VOID Destroy()
	{
		RemoveShader("PrincipledBRDF/DeferredGeometry");
		RemoveShader("PrincipledBRDF/DeferredLighting");

		RemoveShader("PostProcess/PassThrough");

		RemoveShader("Gizmo/Line");
		RemoveShader("Gizmo/Quad");

		RemoveShader("Gizmo/LineBatch");
		RemoveShader("Gizmo/QuadBatch");

		RemoveShader("SkyBox/Default");
	}

	Shader* GetShaderByName(std::string const& ShaderName)
	{
		if (m_Shaders.find(ShaderName) != m_Shaders.end())
		{
			return m_Shaders[ShaderName];
		}

		return nullptr;
	}

	Shader* AddShader(std::string const& ShaderName)
	{
		if (m_Shaders.find(ShaderName) == m_Shaders.end())
		{
			return m_Shaders[ShaderName] = new (Memory::Alloc(sizeof(Shader))) Shader;
		}

		return nullptr;
	}

	VOID RemoveShader(std::string const& ShaderName)
	{
		auto Iter = m_Shaders.find(ShaderName);

		if (Iter != m_Shaders.end())
		{
			Shader* Shader = Iter->second;

			Shader->~Shader();

			Memory::Free(Shader);

			m_Shaders.erase(Iter);
		}
	}
}