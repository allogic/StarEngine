#pragma once

namespace StarEngine
{
	class Texture2DReference : public AssetReference
	{
	public:

		Texture2DReference();

		virtual ~Texture2DReference();

	public:

		inline Texture2D const* GetTexture2D() const { return _Texture; }

	public:

		inline VOID SetFilePath(fs::path const& TextureFilePath) { _TextureFilePath = TextureFilePath; }
		inline VOID SetGenerateMipMaps(BOOL GenerateMipMaps) { _GenerateMipMaps = GenerateMipMaps; }

	public:

		VOID Reload() override;
		
	private:

		Texture2D* _Texture = nullptr;

		fs::path _TextureFilePath = "";

		BOOL _GenerateMipMaps = false;
	};
}