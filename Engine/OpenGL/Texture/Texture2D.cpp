#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Texture/Texture2D.h>

namespace StarEngine
{
	Texture2D::Texture2D()
	{
		glGenTextures(1, &_Texture);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &_Texture);
	}

	VOID Texture2D::UpdateBuffer(VOID const* Buffer, BOOL const GenerateMipMaps)
	{
		glBindTexture(GL_TEXTURE_2D, _Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _WrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _WrapT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _MinFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _MagFilter);

		glTexImage2D(GL_TEXTURE_2D, 0, _InternalFormat, _Width, _Height, 0, _Format, _Type, Buffer);

		if (GenerateMipMaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	VOID Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, _Texture);
	}

	VOID Texture2D::Mount(U32 const Index) const
	{
		glBindTextureUnit(Index, _Texture);
	}

	VOID Texture2D::Unmount(U32 const Index) const
	{
		glBindTextureUnit(Index, 0);
	}

	VOID Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}