#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/FrameBuffer/DeferredGeometryFrameBuffer.h>

#include <Engine/OpenGL/Texture/Texture2D.h>

namespace StarEngine
{
	DeferredGeometryFrameBuffer::DeferredGeometryFrameBuffer(U32 const Width, U32 const Height)
	{
		_Width = Width;
		_Height = Height;

		CreateFrameBufferAndAttachments();
	}

	DeferredGeometryFrameBuffer::~DeferredGeometryFrameBuffer()
	{
		DestroyFrameBufferAndAttachments();
	}

	VOID DeferredGeometryFrameBuffer::BindRead()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DeferredGeometryFrameBuffer::BindWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DeferredGeometryFrameBuffer::BindReadWrite()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer);
	}

	VOID DeferredGeometryFrameBuffer::UnbindRead()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	VOID DeferredGeometryFrameBuffer::UnbindWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	VOID DeferredGeometryFrameBuffer::UnbindReadWrite()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	VOID DeferredGeometryFrameBuffer::Resize(U32 const Width, U32 const Height)
	{
		if ((_Width != Width) || (_Height != Height))
		{
			DestroyFrameBufferAndAttachments();

			_Width = Width;
			_Height = Height;

			CreateFrameBufferAndAttachments();
		}
	}

	VOID DeferredGeometryFrameBuffer::CreateFrameBufferAndAttachments()
	{
		glGenFramebuffers(1, &_FrameBuffer);

		glBindFramebuffer(GL_FRAMEBUFFER, _FrameBuffer);

		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, _Width);
		glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, _Height);

		_WorldPositionTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_WorldNormalTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_AlbedoTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_NormalTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_TangentTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_BitangentTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_MRAOTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;
		_DepthStencilTexture = new (Memory::Alloc(sizeof(Texture2D))) Texture2D;

		_WorldPositionTexture->SetWidth(_Width);
		_WorldPositionTexture->SetHeight(_Height);
		_WorldPositionTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_WorldPositionTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_WorldPositionTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_WorldPositionTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_WorldPositionTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_WorldPositionTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_WorldPositionTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_WorldPositionTexture->UpdateBuffer(nullptr, false);

		_WorldNormalTexture->SetWidth(_Width);
		_WorldNormalTexture->SetHeight(_Height);
		_WorldNormalTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_WorldNormalTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_WorldNormalTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_WorldNormalTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_WorldNormalTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_WorldNormalTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_WorldNormalTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_WorldNormalTexture->UpdateBuffer(nullptr, false);

		_AlbedoTexture->SetWidth(_Width);
		_AlbedoTexture->SetHeight(_Height);
		_AlbedoTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_AlbedoTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_AlbedoTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_AlbedoTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_AlbedoTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_AlbedoTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_AlbedoTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_AlbedoTexture->UpdateBuffer(nullptr, false);

		_NormalTexture->SetWidth(_Width);
		_NormalTexture->SetHeight(_Height);
		_NormalTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_NormalTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_NormalTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_NormalTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_NormalTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_NormalTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_NormalTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_NormalTexture->UpdateBuffer(nullptr, false);

		_TangentTexture->SetWidth(_Width);
		_TangentTexture->SetHeight(_Height);
		_TangentTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_TangentTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_TangentTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_TangentTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_TangentTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_TangentTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_TangentTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_TangentTexture->UpdateBuffer(nullptr, false);

		_BitangentTexture->SetWidth(_Width);
		_BitangentTexture->SetHeight(_Height);
		_BitangentTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_BitangentTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_BitangentTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_BitangentTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_BitangentTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_BitangentTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_BitangentTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_BitangentTexture->UpdateBuffer(nullptr, false);

		_MRAOTexture->SetWidth(_Width);
		_MRAOTexture->SetHeight(_Height);
		_MRAOTexture->SetWrapS(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_MRAOTexture->SetWrapT(TextureWrap::TEXTURE_WRAP_CLAMP_TO_BORDER);
		_MRAOTexture->SetMinFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_MRAOTexture->SetMagFilter(TextureFilter::TEXTURE_FILTER_NEAREST);
		_MRAOTexture->SetType(TextureType::TEXTURE_TYPE_R32);
		_MRAOTexture->SetFormat(TextureFormat::TEXTURE_FORMAT_RGB);
		_MRAOTexture->SetInternalFormat(TextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGB_R32);
		_MRAOTexture->UpdateBuffer(nullptr, false);

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

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _WorldPositionTexture->GetTexture(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _WorldNormalTexture->GetTexture(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _AlbedoTexture->GetTexture(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, _NormalTexture->GetTexture(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, _TangentTexture->GetTexture(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, _BitangentTexture->GetTexture(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, _MRAOTexture->GetTexture(), 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _DepthStencilTexture->GetTexture(), 0);

		U32 BufferAttachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6 };

		glDrawBuffers(7, BufferAttachments);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	VOID DeferredGeometryFrameBuffer::DestroyFrameBufferAndAttachments()
	{
		_WorldPositionTexture->~Texture2D();
		_WorldNormalTexture->~Texture2D();
		_AlbedoTexture->~Texture2D();
		_NormalTexture->~Texture2D();
		_TangentTexture->~Texture2D();
		_BitangentTexture->~Texture2D();
		_MRAOTexture->~Texture2D();
		_DepthStencilTexture->~Texture2D();

		Memory::Free(_WorldPositionTexture);
		Memory::Free(_WorldNormalTexture);
		Memory::Free(_AlbedoTexture);
		Memory::Free(_NormalTexture);
		Memory::Free(_TangentTexture);
		Memory::Free(_BitangentTexture);
		Memory::Free(_MRAOTexture);
		Memory::Free(_DepthStencilTexture);

		glDeleteFramebuffers(1, &_FrameBuffer);
	}
}