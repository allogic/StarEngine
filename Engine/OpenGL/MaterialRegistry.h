#pragma once

namespace StarEngine::MaterialRegistry
{
	VOID Create(fs::path const& TextureFilePath);
	VOID Destroy();

	Material* GetMaterialByName(std::string const& MaterialName);

	Material* AddMaterial(std::string const& MaterialName);
	VOID RemoveMaterial(std::string const& MaterialName);
}