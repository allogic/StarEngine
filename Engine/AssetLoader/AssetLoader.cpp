#include <Engine/PreCompiled.h>
#include <Engine/Model.h>

#include <Engine/JSON/json.hpp>

#include <Engine/AssetLoader/FileObserver.h>
#include <Engine/AssetLoader/WatchDog.h>

#include <Engine/Utility/FileSystem.h>
#include <Engine/Utility/StringUtility.h>

#define SE_SET_MATERIAL_REFERENCE_BY_NAME(ENTRY, NAME) \
	if (ENTRY[NAME].is_string()) \
	{ \
		Reference.SetTextureReferenceByName(NAME, GetTexture2DByName(ENTRY[NAME])); \
	} \
	else if (ENTRY[NAME].is_number_float()) \
	{ \
		Reference.SetTextureAttenuatorByName(NAME, ENTRY[NAME]); \
	}

namespace StarEngine::AssetLoader
{
	static WatchDog* m_AssetWatchDog = nullptr;

	static std::map<std::string, MaterialReference> m_MaterialReferences = {};
	static std::map<std::string, ModelReference> m_ModelReferences = {};
	static std::map<std::string, ShaderReference> m_ShaderReferences = {};
	static std::map<std::string, SkyBoxReference> m_SkyBoxReferences = {};
	static std::map<std::string, Texture2DReference> m_Texture2DReferences = {};

	static VOID CreateAsset(fs::path const& AssetFilePath, nlohmann::json const& Asset);
	static VOID ModifyAsset(fs::path const& AssetFilePath, nlohmann::json const& Asset);
	static VOID DeleteAsset(fs::path const& AssetFilePath, nlohmann::json const& Asset);

	static VOID CreateModel(fs::path const& AssetFilePath, nlohmann::json const& ModelEntry);
	static VOID CreateMaterial(fs::path const& AssetFilePath, nlohmann::json const& MaterialEntry);
	static VOID CreateShader(fs::path const& AssetFilePath, nlohmann::json const& ShaderEntry);
	static VOID CreateSkyBox(fs::path const& AssetFilePath, nlohmann::json const& SkyBoxEntry);
	static VOID CreateTexture2D(fs::path const& AssetFilePath, nlohmann::json const& TextureEntry);

	VOID Create(fs::path const& AssetFilePath)
	{
		m_AssetWatchDog = new (Memory::Alloc(sizeof(WatchDog))) WatchDog(AssetFilePath, ".json");
	}

	VOID Destroy()
	{
		// TODO

		m_AssetWatchDog->~WatchDog();

		Memory::Free(m_AssetWatchDog);
	}

	VOID Update()
	{
		m_AssetWatchDog->Update();

		for (auto const& AssetFilePath : m_AssetWatchDog->GetFilesDeleted())
		{
			std::string AssetString = "";

			FileSystem::ReadTextFile(AssetFilePath, AssetString);

			nlohmann::json Asset = nlohmann::json::parse(AssetString);

			DeleteAsset(AssetFilePath.parent_path(), Asset);
		}

		for (auto const& AssetFilePath : m_AssetWatchDog->GetFilesModified())
		{
			std::string AssetString = "";

			FileSystem::ReadTextFile(AssetFilePath, AssetString);

			nlohmann::json Asset = nlohmann::json::parse(AssetString);

			ModifyAsset(AssetFilePath.parent_path(), Asset);
		}

		for (auto const& AssetFilePath : m_AssetWatchDog->GetFilesCreated())
		{
			std::string AssetString = "";

			FileSystem::ReadTextFile(AssetFilePath, AssetString);

			nlohmann::json Asset = nlohmann::json::parse(AssetString);

			CreateAsset(AssetFilePath.parent_path(), Asset);
		}
	}

	MaterialReference const* GetMaterialByName(std::string const& MaterialName)
	{
		return (MaterialReference const*)&m_MaterialReferences[MaterialName];
	}

	ModelReference const* GetModelByName(std::string const& ModelName)
	{
		return (ModelReference const*)&m_ModelReferences[ModelName];
	}

	ShaderReference const* GetShaderByName(std::string const& ShaderName)
	{
		return (ShaderReference const*)&m_ShaderReferences[ShaderName];
	}

	SkyBoxReference const* GetSkyBoxByName(std::string const& SkyBoxName)
	{
		return (SkyBoxReference const*)&m_SkyBoxReferences[SkyBoxName];
	}

	Texture2DReference const* GetTexture2DByName(std::string const& TextureName)
	{
		return (Texture2DReference*)&m_Texture2DReferences[TextureName];
	}

	static VOID CreateAsset(fs::path const& AssetFilePath, nlohmann::json const& Asset)
	{
		nlohmann::json const& Config = Asset["Config"];

		std::string const Type = Config["Type"];

		if (Type == "Model")
		{
			nlohmann::json const& Models = Asset["Models"];
			nlohmann::json const& Materials = Asset["Materials"];
			nlohmann::json const& Textures = Asset["Textures"];

			for (auto const& Model : Models)
			{
				CreateModel(AssetFilePath, Model);
			}

			for (auto const& Material : Materials)
			{
				CreateMaterial(AssetFilePath, Material);
			}

			for (auto const& Texture : Textures)
			{
				CreateTexture2D(AssetFilePath, Texture);
			}
		}
		else if (Type == "Shader")
		{
			nlohmann::json const& Shaders = Asset["Shaders"];

			for (auto const& Shader : Shaders)
			{
				CreateShader(AssetFilePath, Shader);
			}
		}
		else if (Type == "SkyBox")
		{
			nlohmann::json const& SkyBoxes = Asset["SkyBoxes"];
			nlohmann::json const& Materials = Asset["Materials"];
			nlohmann::json const& Textures = Asset["Textures"];

			for (auto const& SkyBox : SkyBoxes)
			{
				CreateSkyBox(AssetFilePath, SkyBox);
			}

			for (auto const& Material : Materials)
			{
				CreateMaterial(AssetFilePath, Material);
			}

			for (auto const& Texture : Textures)
			{
				CreateTexture2D(AssetFilePath, Texture);
			}
		}
	}

	static VOID ModifyAsset(fs::path const& AssetFilePath, nlohmann::json const& Asset)
	{

	}

	static VOID DeleteAsset(fs::path const& AssetFilePath, nlohmann::json const& Asset)
	{

	}

	static VOID CreateModel(fs::path const& AssetFilePath, nlohmann::json const& ModelEntry)
	{
		std::string ModelName = ModelEntry["Name"];

		fs::path ModelFilePath = AssetFilePath / ModelEntry["FilePath"];

		ModelFilePath = StringUtility::ReplaceCharacter(ModelFilePath.string(), '/', '\\');

		ModelReference& Reference = m_ModelReferences[ModelName];

		Reference.SetModelFilePath(ModelFilePath);

		Reference.Reload();
	}

	static VOID CreateMaterial(fs::path const& AssetFilePath, nlohmann::json const& MaterialEntry)
	{
		std::string MaterialName = MaterialEntry["Name"];
		std::string ShaderName = MaterialEntry["Shader"];

		MaterialReference& Reference = m_MaterialReferences[MaterialName];

		Reference.SetMaterialReference(GetShaderByName(ShaderName));

		if (ShaderName == "DeferredGeometry")
		{
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Albedo");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Normal");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Metallic");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Roughness");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "AmbientOcclusion");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Height");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Emissive");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Opacity");
		}
		else if (ShaderName == "SpaceBox")
		{
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Front");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Back");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Left");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Right");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Top");
			SE_SET_MATERIAL_REFERENCE_BY_NAME(MaterialEntry, "Bottom");
		}
		else
		{
			assert(1);
		}

		Reference.Reload();
	}

	static VOID CreateShader(fs::path const& AssetFilePath, nlohmann::json const& ShaderEntry)
	{
		std::string const ShaderName = ShaderEntry["Name"];

		fs::path VertexShaderFilePath = AssetFilePath / ShaderEntry["VertexShaderFilePath"];
		fs::path FragmentShaderFilePath = AssetFilePath / ShaderEntry["FragmentShaderFilePath"];

		VertexShaderFilePath = StringUtility::ReplaceCharacter(VertexShaderFilePath.string(), '/', '\\');
		FragmentShaderFilePath = StringUtility::ReplaceCharacter(FragmentShaderFilePath.string(), '/', '\\');

		ShaderReference& Reference = m_ShaderReferences[ShaderName];

		Reference.SetVertexShaderFilePath(VertexShaderFilePath);
		Reference.SetFragmentShaderFilePath(FragmentShaderFilePath);

		Reference.Reload();
	}

	static VOID CreateSkyBox(fs::path const& AssetFilePath, nlohmann::json const& SkyBoxEntry)
	{

	}

	static VOID CreateTexture2D(fs::path const& AssetFilePath, nlohmann::json const& TextureEntry)
	{
		std::string TextureName = TextureEntry["Name"];

		fs::path TextureFilePath = AssetFilePath / TextureEntry["FilePath"];
		BOOL GenerateMipMaps = TextureEntry["GenerateMipMaps"];

		TextureFilePath = StringUtility::ReplaceCharacter(TextureFilePath.string(), '/', '\\');

		Texture2DReference& Reference = m_Texture2DReferences[TextureName];

		Reference.SetFilePath(TextureFilePath);
		Reference.SetGenerateMipMaps(GenerateMipMaps);

		Reference.Reload();
	}
}