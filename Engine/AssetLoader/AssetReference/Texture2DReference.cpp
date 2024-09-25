#include <Engine/PreCompiled.h>

#include <Engine/OpenGL/Texture/Texture2D.h>

#include <Engine/Utility/FileSystem.h>

namespace StarEngine
{
	Texture2DReference::Texture2DReference()
		: AssetReference()
	{

	}

	Texture2DReference::~Texture2DReference()
	{

	}

	VOID Texture2DReference::Reload()
	{
		assert(_Texture == nullptr);

		_Texture = new (Memory::Alloc(sizeof(Texture2D))) StarEngine::Texture2D;

		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(_TextureFilePath, Buffer, Width, Height, Channels);

		_Texture->SetWidth(Width);
		_Texture->SetHeight(Height);
		_Texture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_Texture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_Texture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_Texture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_Texture->SetType(TextureType::TEXTURE_TYPE_U8);

		switch (Channels)
		{
			case 4:
			{
				_Texture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGBA);
				_Texture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA);

				break;
			}
			case 3:
			{
				_Texture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
				_Texture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB);

				break;
			}
			case 2:
			{
				_Texture->SetFormat(TextureFormat::TEXTURE_FORMAT_RG);
				_Texture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RG);

				break;
			}
			case 1:
			{
				_Texture->SetFormat(TextureFormat::TEXTURE_FORMAT_R);
				_Texture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_R);

				break;
			}
		}

		_Texture->UpdateBuffer(Buffer.data(), _GenerateMipMaps);
	}
}