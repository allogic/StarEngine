#pragma once

#include <Engine/OpenGL/Texture/TextureFilter.h>

namespace StarEngine
{
	class DeferredLightingFrameBuffer
	{
	public:

		DeferredLightingFrameBuffer(U32 const Width, U32 const Height);

		virtual ~DeferredLightingFrameBuffer();

	public:

		inline Texture2D* GetColorTexture() const { return _ColorTexture; }

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

		Texture2D* _ColorTexture = nullptr;
	};
}