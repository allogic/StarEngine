#pragma once

namespace StarEngine::ModelRegistry
{
	VOID Create(fs::path const& ModelFilePath);
	VOID Destroy();

	Model* GetModelByName(std::string const& ModelName);

	Model* AddModel(std::string const& ModelName);
	VOID RemoveModel(std::string const& ModelName);
}