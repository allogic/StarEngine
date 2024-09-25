#include <Engine/PreCompiled.h>

#include <Engine/OpenGL/Shader/Shader.h>

namespace StarEngine
{
	ShaderReference::ShaderReference()
		: AssetReference()
	{

	}

	ShaderReference::~ShaderReference()
	{

	}

	VOID ShaderReference::Reload()
	{
		assert(_Shader == nullptr);

		_Shader = new (Memory::Alloc(sizeof(Shader))) StarEngine::Shader(_VertexShaderFilePath, _FragmentShaderFilePath);
	}
}