#include <Engine/PreCompiled.h>

#include <Engine/OpenGL/Material.h>
#include <Engine/OpenGL/MaterialRegistry.h>

#include <Engine/OpenGL/Shader/Shader.h>
#include <Engine/OpenGL/Shader/ShaderRegistry.h>

namespace StarEngine::MaterialRegistry
{
	static std::map<std::string, Material*> m_Materials = {};

	VOID Create(fs::path const& TextureFilePath)
	{
		Shader* DeferredGeometry = ShaderRegistry::GetShaderByName("PrincipledBRDF/DeferredGeometry");
		Shader* DefaultSkyBox = ShaderRegistry::GetShaderByName("SkyBox/Default");

		Material* Cockpit = AddMaterial("Cockpit/Cockpit");
		Material* Screen = AddMaterial("Cockpit/Screen");
		Material* Window = AddMaterial("Cockpit/Window");
		Material* SkyBox = AddMaterial("SkyBox/Space");

		Cockpit->SetName("Cockpit/Cockpit");
		Cockpit->SetShader(DeferredGeometry);
		Cockpit->LoadAlbedoTexture(TextureFilePath / "Cockpit" / "Cockpit" / "Albedo.png");
		Cockpit->LoadNormalTexture(TextureFilePath / "Cockpit" / "Cockpit" / "Normal.png");
		Cockpit->LoadMetallicTexture(TextureFilePath / "Cockpit" / "Cockpit" / "Metallic.png");
		Cockpit->LoadRoughnessTexture(TextureFilePath / "Cockpit" / "Cockpit" / "Roughness.png");
		Cockpit->LoadAmbientOcclusionTexture(TextureFilePath / "Cockpit" / "Cockpit" / "AmbientOcclusion.png");
		Cockpit->LoadHeightTexture(TextureFilePath / "Cockpit" / "Cockpit" / "Height.png");
		Cockpit->LoadEmissiveTexture(TextureFilePath / "Cockpit" / "Cockpit" / "Emissive.png");

		Screen->SetName("Cockpit/Screen");
		Screen->SetShader(DeferredGeometry);
		Screen->LoadAlbedoTexture(TextureFilePath / "Cockpit" / "Screen" / "Albedo.png");
		Screen->LoadMetallicTexture(TextureFilePath / "Cockpit" / "Screen" / "Metallic.png");
		Screen->LoadRoughnessTexture(TextureFilePath / "Cockpit" / "Screen" / "Roughness.png");
		Screen->LoadAmbientOcclusionTexture(TextureFilePath / "Cockpit" / "Screen" / "AmbientOcclusion.png");

		Window->SetName("Cockpit/Window");
		Window->SetShader(DeferredGeometry);
		Window->LoadAlbedoTexture(TextureFilePath / "Cockpit" / "Window" / "Albedo.png");
		Window->LoadMetallicTexture(TextureFilePath / "Cockpit" / "Window" / "Metallic.png");
		Window->LoadRoughnessTexture(TextureFilePath / "Cockpit" / "Window" / "Roughness.png");
		Window->LoadAmbientOcclusionTexture(TextureFilePath / "Cockpit" / "Window" / "AmbientOcclusion.png");
		Window->LoadOpacityTexture(TextureFilePath / "Cockpit" / "Window" / "Opacity.png");

		SkyBox->SetName("SkyBox/Space");
		SkyBox->SetShader(DefaultSkyBox);
		SkyBox->LoadCubeMap(TextureFilePath / "Space");
	}

	VOID Destroy()
	{
		RemoveMaterial("Cockpit/Cockpit");
		RemoveMaterial("Cockpit/Screen");
		RemoveMaterial("Cockpit/Window");

		RemoveMaterial("SkyBox/Space");
	}

	Material* GetMaterialByName(std::string const& MaterialName)
	{
		if (m_Materials.find(MaterialName) != m_Materials.end())
		{
			return m_Materials[MaterialName];
		}

		return nullptr;
	}

	Material* AddMaterial(std::string const& MaterialName)
	{
		if (m_Materials.find(MaterialName) == m_Materials.end())
		{
			return m_Materials[MaterialName] = new (Memory::Alloc(sizeof(Material))) Material;
		}

		return nullptr;
	}

	VOID RemoveMaterial(std::string const& MaterialName)
	{
		auto Iter = m_Materials.find(MaterialName);

		if (Iter != m_Materials.end())
		{
			Material* Material = Iter->second;

			Material->~Material();

			Memory::Free(Material);

			m_Materials.erase(Iter);
		}
	}
}