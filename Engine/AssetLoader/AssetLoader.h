#pragma once

namespace StarEngine::AssetLoader
{
	VOID Create(fs::path const& AssetFilePath);
	VOID Destroy();

	VOID Update();

	MaterialReference const* GetMaterialByName(std::string const& MaterialName);
	ModelReference const* GetModelByName(std::string const& ModelName);
	ShaderReference const* GetShaderByName(std::string const& ShaderName);
	SkyBoxReference const* GetSkyBoxByName(std::string const& SkyBoxName);
	Texture2DReference const* GetTexture2DByName(std::string const& TextureName);
}