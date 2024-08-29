#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/FrameBuffer/DeferredLightingFrameBuffer.h>

#include <Engine/OpenGL/Texture/Texture2D.h>

namespace StarEngine
{
	DeferredLightingFrameBuffer::DeferredLightingFrameBuffer(U32 const Width, U32 const Height)
	{
		_Width = Width;
		_Height = Height;

		CreateFrameBufferAndAttachments();
	}

	DeferredLightingFrameBuffer::~DeferredLightingFrameBuffer()
	{
		DestroyFrameBufferAndAttachments();
	}

	VOID DeferredLightingFrameBuffer::BindRead()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DeferredLightingFrameBuffer::BindWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DeferredLightingFrameBuffer::BindReadWrite()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DeferredLightingFrameBuffer::UnbindRead()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	VOID DeferredLightingFrameBuffer::UnbindWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	VOID DeferredLightingFrameBuffer::UnbindReadWrite()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	VOID DeferredLightingFrameBuffer::Resize(U32 const Width, U32 const Height)
	{
		if ((_Width != Width) || (_Height != Height))
		{
			DestroyFrameBufferAndAttachments();

			_Width = Width;
			_Height = Height;

			CreateFrameBufferAndAttachments();
		}
	}

	VOID DeferredLightingFrameBuffer::CreateFrameBufferAndAttachments()
	{
		glGenFramebuffers(1, &_FrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer);

		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, _Width);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, _Height);

		_ColorTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_ColorTexture->SetWidth(_Width);
		_ColorTexture->SetHeight(_Height);
		_ColorTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_ColorTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_ColorTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_ColorTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_ColorTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_ColorTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_ColorTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_ColorTexture->UpdateBuffer(nullptr, false);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ColorTexture->GetTexture(), 0);

		U32 BufferAttachments[] = { GL_COLOR_ATTACHMENT0 };

		glDrawBuffers(1, BufferAttachments);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	VOID DeferredLightingFrameBuffer::DestroyFrameBufferAndAttachments()
	{
		_ColorTexture->~Texture2D();

		Memory::Free(_ColorTexture);

		glDeleteFramebuffers(1, &_FrameBuffer);
	}
}