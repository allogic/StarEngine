#pragma once

namespace StarEngine::ShaderRegistry
{
	VOID Create(fs::path const& ShaderFilePath);
	VOID Destroy();

	Shader* GetShaderByName(std::string const& ShaderName);

	Shader* AddShader(std::string const& ShaderName);
	VOID RemoveShader(std::string const& ShaderName);
}