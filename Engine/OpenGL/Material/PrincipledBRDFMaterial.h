#pragma once

namespace StarEngine
{
	class PrincipledBRDFMaterial : public Material
	{
	public:

		PrincipledBRDFMaterial();

		virtual ~PrincipledBRDFMaterial();

	public:

		inline Texture2DReference const* GetAlbedoTextureReference() const { return _AlbedoTextureReference; }
		inline Texture2DReference const* GetNormalTextureReference() const { return _NormalTextureReference; }
		inline Texture2DReference const* GetMetallicTextureReference() const { return _MetallicTextureReference; }
		inline Texture2DReference const* GetRoughnessTextureReference() const { return _RoughnessTextureReference; }
		inline Texture2DReference const* GetAmbientOcclusionTextureReference() const { return _AmbientOcclusionTextureReference; }
		inline Texture2DReference const* GetHeightTextureReference() const { return _HeightTextureReference; }
		inline Texture2DReference const* GetEmissiveTextureReference() const { return _EmissiveTextureReference; }
		inline Texture2DReference const* GetOpacityTextureReference() const { return _OpacityTextureReference; }

	private:

		Texture2DReference const* _AlbedoTextureReference = nullptr;
		Texture2DReference const* _NormalTextureReference = nullptr;
		Texture2DReference const* _MetallicTextureReference = nullptr;
		Texture2DReference const* _RoughnessTextureReference = nullptr;
		Texture2DReference const* _AmbientOcclusionTextureReference = nullptr;
		Texture2DReference const* _HeightTextureReference = nullptr;
		Texture2DReference const* _EmissiveTextureReference = nullptr;
		Texture2DReference const* _OpacityTextureReference = nullptr;
	};
}