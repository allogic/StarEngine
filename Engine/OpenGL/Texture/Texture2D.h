#pragma once

#include <Engine/OpenGL/Texture/TextureFilter.h>
#include <Engine/OpenGL/Texture/TextureFormat.h>
#include <Engine/OpenGL/Texture/TextureInternalFormat.h>
#include <Engine/OpenGL/Texture/TextureType.h>
#include <Engine/OpenGL/Texture/TextureWrap.h>

namespace StarEngine
{
	class Texture2D
	{
	public:

		Texture2D();

		virtual ~Texture2D();

	public:

		inline U32 GetTexture() const { return _Texture; }

	public:

		inline VOID SetWidth(U32 const Width) { _Width = Width; }
		inline VOID SetHeight(U32 const Height) { _Height = Height; }
		inline VOID SetWrapS(TextureWrap const WrapS) { _WrapS = WrapS; }
		inline VOID SetWrapT(TextureWrap const WrapT) { _WrapT = WrapT; }
		inline VOID SetMinFilter(TextureFilter const MinFilter) { _MinFilter = MinFilter; }
		inline VOID SetMagFilter(TextureFilter const MagFilter) { _MagFilter = MagFilter; }
		inline VOID SetType(TextureType const Type) { _Type = Type; }
		inline VOID SetFormat(TextureFormat const Format) { _Format = Format; }
		inline VOID SetInternalFormat(TextureInternalFormat const InternalFormat) { _InternalFormat = InternalFormat; }

	public:

		VOID UpdateBuffer(VOID const* Buffer, BOOL const GenerateMipMaps);

	public:

		VOID Bind() const;
		VOID Mount(U32 const Index) const;
		VOID Unmount(U32 const Index) const;
		VOID Unbind() const;

	private:

		U32 _Texture = 0;
		U32 _Width = 0;
		U32 _Height = 0;

		TextureWrap _WrapS = TEXTURE_WRAP_NONE;
		TextureWrap _WrapT = TEXTURE_WRAP_NONE;

		TextureFilter _MinFilter = TEXTURE_FILTER_NONE;
		TextureFilter _MagFilter = TEXTURE_FILTER_NONE;

		TextureType _Type = TEXTURE_TYPE_NONE;

		TextureFormat _Format = TEXTURE_FORMAT_NONE;
		TextureInternalFormat _InternalFormat = TEXTURE_INTERNAL_FORMAT_NONE;
	};
}