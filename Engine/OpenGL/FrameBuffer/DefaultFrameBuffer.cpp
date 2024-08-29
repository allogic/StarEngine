#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/FrameBuffer/DefaultFrameBuffer.h>

#include <Engine/OpenGL/Texture/Texture2D.h>

namespace StarEngine
{
	DefaultFrameBuffer::DefaultFrameBuffer(U32 const Width, U32 const Height)
	{
		_Width = Width;
		_Height = Height;

		CreateFrameBufferAndAttachments();
	}

	DefaultFrameBuffer::~DefaultFrameBuffer()
	{
		DestroyFrameBufferAndAttachments();
	}

	VOID DefaultFrameBuffer::BindRead()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DefaultFrameBuffer::BindWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DefaultFrameBuffer::BindReadWrite()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DefaultFrameBuffer::UnbindRead()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	VOID DefaultFrameBuffer::UnbindWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	VOID DefaultFrameBuffer::UnbindReadWrite()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	VOID DefaultFrameBuffer::Resize(U32 const Width, U32 const Height)
	{
		if ((_Width != Width) || (_Height != Height))
		{
			DestroyFrameBufferAndAttachments();

			_Width = Width;
			_Height = Height;

			CreateFrameBufferAndAttachments();
		}
	}

	VOID DefaultFrameBuffer::CreateFrameBufferAndAttachments()
	{
		glGenFramebuffers(1, &_FrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer);

		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, _Width);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, _Height);

		_ColorTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_DepthStencilTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

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

		_DepthStencilTexture->SetWidth(_Width);
		_DepthStencilTexture->SetHeight(_Height);
		_DepthStencilTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_DepthStencilTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_DepthStencilTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_DepthStencilTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_DepthStencilTexture->SetType(TextureType::TEXTURE_TYPE_U24_U8);
		_DepthStencilTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_DEPTH_STENCIL);
		_DepthStencilTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8);
		_DepthStencilTexture->UpdateBuffer(nullptr, false);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ColorTexture->GetTexture(), 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _DepthStencilTexture->GetTexture(), 0);

		U32 BufferAttachments[] = { GL_COLOR_ATTACHMENT0 };

		glDrawBuffers(1, BufferAttachments);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	VOID DefaultFrameBuffer::DestroyFrameBufferAndAttachments()
	{
		_ColorTexture->~Texture2D();
		_DepthStencilTexture->~Texture2D();

		Memory::Free(_ColorTexture);
		Memory::Free(_DepthStencilTexture);

		glDeleteFramebuffers(1, &_FrameBuffer);
	}
}