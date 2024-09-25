#pragma once

namespace StarEngine
{
	class MaterialReference : public AssetReference
	{
	public:

		MaterialReference();

		virtual ~MaterialReference();

	public:

		inline Material const* GetMaterial() const { return _Material; }

		inline ShaderReference const* GetShaderReference() const { return _ShaderReference; }

	public:

		inline VOID SetMaterialReference(ShaderReference const* ShaderReference) { _ShaderReference = ShaderReference; }

	public:

		VOID SetTextureReferenceByName(std::string const& TextureName, Texture2DReference const* Texture2DReference);
		VOID SetTextureAttenuatorByName(std::string const& TextureName, R32 Attenuator);

	public:

		VOID Reload() override;

	private:

		Material* _Material = nullptr;

		ShaderReference const* _ShaderReference = nullptr;

		std::map<std::string, Texture2DReference const*> _Texture2DReferences = {};
		std::map<std::string, R32> _Texture2DAttenuators = {};
	};
}