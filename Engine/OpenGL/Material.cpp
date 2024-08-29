#include <Engine/PreCompiled.h>

#include <Engine/OpenGL/Material.h>

#include <Engine/OpenGL/Texture/CubeMap.h>
#include <Engine/OpenGL/Texture/Texture2D.h>

#include <Engine/Utility/FileSystem.h>

namespace StarEngine
{
	Material::Material()
	{

	}

	Material::~Material()
	{
		if (_AlbedoTexture) _AlbedoTexture->~Texture2D();
		if (_NormalTexture) _NormalTexture->~Texture2D();
		if (_MetallicTexture) _MetallicTexture->~Texture2D();
		if (_RoughnessTexture) _RoughnessTexture->~Texture2D();
		if (_AmbientOcclusionTexture) _AmbientOcclusionTexture->~Texture2D();
		if (_HeightTexture) _HeightTexture->~Texture2D();
		if (_EmissiveTexture) _EmissiveTexture->~Texture2D();
		if (_OpacityTexture) _OpacityTexture->~Texture2D();

		if (_CubeMap) _CubeMap->~CubeMap();

		if (_AlbedoTexture) Memory::Free(_AlbedoTexture);
		if (_NormalTexture) Memory::Free(_NormalTexture);
		if (_MetallicTexture) Memory::Free(_MetallicTexture);
		if (_RoughnessTexture) Memory::Free(_RoughnessTexture);
		if (_AmbientOcclusionTexture) Memory::Free(_AmbientOcclusionTexture);
		if (_HeightTexture) Memory::Free(_HeightTexture);
		if (_EmissiveTexture) Memory::Free(_EmissiveTexture);
		if (_OpacityTexture) Memory::Free(_OpacityTexture);

		if (_CubeMap) Memory::Free(_CubeMap);
	}

	Texture2D* Material::LoadAlbedoTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_AlbedoTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_AlbedoTexture->SetWidth(Width);
		_AlbedoTexture->SetHeight(Height);
		_AlbedoTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_AlbedoTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_AlbedoTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_AlbedoTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_AlbedoTexture->SetType(TextureType::TEXTURE_TYPE_U8);

		switch (Channels)
		{
			case 4:
			{
				_AlbedoTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGBA);
				_AlbedoTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA);

				break;
			}
			case 3:
			{
				_AlbedoTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
				_AlbedoTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB);

				break;
			}
		}

		_AlbedoTexture->UpdateBuffer(Buffer.data(), true);

		return _AlbedoTexture;
	}

	Texture2D* Material::LoadNormalTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_NormalTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_NormalTexture->SetWidth(Width);
		_NormalTexture->SetHeight(Height);
		_NormalTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_NormalTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_NormalTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_NormalTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_NormalTexture->SetType(TextureType::TEXTURE_TYPE_U8);
		_NormalTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_NormalTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB);
		_NormalTexture->UpdateBuffer(Buffer.data(), true);

		return _NormalTexture;
	}

	Texture2D* Material::LoadMetallicTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_MetallicTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_MetallicTexture->SetWidth(Width);
		_MetallicTexture->SetHeight(Height);
		_MetallicTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_MetallicTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_MetallicTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_MetallicTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_MetallicTexture->SetType(TextureType::TEXTURE_TYPE_U8);
		_MetallicTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_R);
		_MetallicTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_R);
		_MetallicTexture->UpdateBuffer(Buffer.data(), true);

		return _MetallicTexture;
	}

	Texture2D* Material::LoadRoughnessTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_RoughnessTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_RoughnessTexture->SetWidth(Width);
		_RoughnessTexture->SetHeight(Height);
		_RoughnessTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_RoughnessTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_RoughnessTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_RoughnessTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_RoughnessTexture->SetType(TextureType::TEXTURE_TYPE_U8);
		_RoughnessTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_R);
		_RoughnessTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_R);
		_RoughnessTexture->UpdateBuffer(Buffer.data(), true);

		return _RoughnessTexture;
	}

	Texture2D* Material::LoadAmbientOcclusionTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_AmbientOcclusionTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_AmbientOcclusionTexture->SetWidth(Width);
		_AmbientOcclusionTexture->SetHeight(Height);
		_AmbientOcclusionTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_AmbientOcclusionTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_AmbientOcclusionTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_AmbientOcclusionTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_AmbientOcclusionTexture->SetType(TextureType::TEXTURE_TYPE_U8);
		_AmbientOcclusionTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_R);
		_AmbientOcclusionTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_R);
		_AmbientOcclusionTexture->UpdateBuffer(Buffer.data(), true);

		return _AmbientOcclusionTexture;
	}

	Texture2D* Material::LoadHeightTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_HeightTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_HeightTexture->SetWidth(Width);
		_HeightTexture->SetHeight(Height);
		_HeightTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_HeightTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_HeightTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_HeightTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_HeightTexture->SetType(TextureType::TEXTURE_TYPE_U8);
		_HeightTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_R);
		_HeightTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_R);
		_HeightTexture->UpdateBuffer(Buffer.data(), true);

		return _HeightTexture;
	}

	Texture2D* Material::LoadEmissiveTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_EmissiveTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_EmissiveTexture->SetWidth(Width);
		_EmissiveTexture->SetHeight(Height);
		_EmissiveTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_EmissiveTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_EmissiveTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_EmissiveTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_EmissiveTexture->SetType(TextureType::TEXTURE_TYPE_U8);
		_EmissiveTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_EmissiveTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB);
		_EmissiveTexture->UpdateBuffer(Buffer.data(), true);

		return _EmissiveTexture;
	}

	Texture2D* Material::LoadOpacityTexture(fs::path const& FilePath)
	{
		std::vector<U8> Buffer = {};

		U32 Width = 0;
		U32 Height = 0;
		U32 Channels = 0;

		FileSystem::ReadImageFile(FilePath, Buffer, Width, Height, Channels);

		_OpacityTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_OpacityTexture->SetWidth(Width);
		_OpacityTexture->SetHeight(Height);
		_OpacityTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_OpacityTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_OpacityTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR);
		_OpacityTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_OpacityTexture->SetType(TextureType::TEXTURE_TYPE_U8);
		_OpacityTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_R);
		_OpacityTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_R);
		_OpacityTexture->UpdateBuffer(Buffer.data(), true);

		return _OpacityTexture;
	}

	CubeMap* Material::LoadCubeMap(fs::path const& FilePath)
	{
		std::vector<fs::path> Faces =
		{
			FilePath / "Right.png",
			FilePath / "Left.png",
			FilePath / "Top.png",
			FilePath / "Bottom.png",
			FilePath / "Back.png",
			FilePath / "Front.png",
		};

		_CubeMap = new (Memory::Alloc(sizeof(CubeMap))) CubeMap;

		_CubeMap->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_EDGE);
		_CubeMap->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_EDGE);
		_CubeMap->SetWrapR(TextureWrap::TEXTURE_WRAP_CLAMP_TO_EDGE);
		_CubeMap->SetMinFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_CubeMap->SetMagFilter(TextureFilter::TEXTURE_FILTER_LINEAR);
		_CubeMap->SetType(TextureType::TEXTURE_TYPE_U8);
		_CubeMap->SetFormat(TextureFormat::TEXTURE_FORMAT_RGBA);
		_CubeMap->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA);

		for (U32 FaceIndex = 0; FaceIndex < 6; FaceIndex++)
		{
			std::vector<U8> Buffer = {};

			U32 Width = 0;
			U32 Height = 0;
			U32 Channels = 0;

			FileSystem::ReadImageFile(Faces[FaceIndex], Buffer, Width, Height, Channels);

			_CubeMap->SetWidth(Width);
			_CubeMap->SetHeight(Height);
			_CubeMap->UpdateBuffer(Buffer.data(), false, FaceIndex);
		}

		return _CubeMap;
	}
}