#pragma once

#include <Engine/OpenGL/Texture/TextureFilter.h>

namespace StarEngine
{
	class DeferredGeometryFrameBuffer
	{
	public:

		DeferredGeometryFrameBuffer(U32 const Width, U32 const Height);

		virtual ~DeferredGeometryFrameBuffer();

	public:

		inline Texture2D* GetWorldPositionTexture() const { return _WorldPositionTexture; }
		inline Texture2D* GetWorldNormalTexture() const { return _WorldNormalTexture; }
		inline Texture2D* GetAlbedoTexture() const { return _AlbedoTexture; }
		inline Texture2D* GetNormalTexture() const { return _NormalTexture; }
		inline Texture2D* GetTangentTexture() const { return _TangentTexture; }
		inline Texture2D* GetBitangentTexture() const { return _BitangentTexture; }
		inline Texture2D* GetMRAOTexture() const { return _MRAOTexture; }
		inline Texture2D* GetDepthStencilTexture() const { return _DepthStencilTexture; }

	public:

		VOID BindRead();
		VOID BindWrite();
		VOID BindReadWrite();

		VOID UnbindRead();
		VOID UnbindWrite();
		VOID UnbindReadWrite();

	public:

		VOID Resize(U32 const Width, U32 const Height);

	private:

		VOID CreateFrameBufferAndAttachments();
		VOID DestroyFrameBufferAndAttachments();

	private:

		U32 _FrameBuffer = 0;
		U32 _Width = 0;
		U32 _Height = 0;

		Texture2D* _WorldPositionTexture = nullptr;
		Texture2D* _WorldNormalTexture = nullptr;
		Texture2D* _AlbedoTexture = nullptr;
		Texture2D* _NormalTexture = nullptr;
		Texture2D* _TangentTexture = nullptr;
		Texture2D* _BitangentTexture = nullptr;
		Texture2D* _MRAOTexture = nullptr;
		Texture2D* _DepthStencilTexture = nullptr;
	};
}