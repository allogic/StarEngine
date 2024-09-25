#pragma once

namespace StarEngine
{
	class ShaderReference : public AssetReference
	{
	public:

		ShaderReference();

		virtual ~ShaderReference();

	public:

		inline Shader* const GetShader() const { return _Shader; }

	public:

		inline VOID SetVertexShaderFilePath(fs::path const& VertexShaderFilePath) { _VertexShaderFilePath = VertexShaderFilePath; }
		inline VOID SetFragmentShaderFilePath(fs::path const& FragmentShaderFilePath) { _FragmentShaderFilePath = FragmentShaderFilePath; }

	public:

		VOID Reload() override;

	private:

		Shader* _Shader = nullptr;

		fs::path _VertexShaderFilePath = "";
		fs::path _FragmentShaderFilePath = "";
	};
}