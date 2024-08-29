#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Texture/CubeMap.h>

namespace StarEngine
{
	CubeMap::CubeMap()
	{
		glGenTextures(1, &_Texture);
	}

	CubeMap::~CubeMap()
	{
		glDeleteTextures(1, &_Texture);
	}

	VOID CubeMap::UpdateBuffer(VOID const* Buffer, BOOL const GenerateMipMaps, U32 const Index)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _Texture);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, _WrapS);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, _WrapT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, _WrapR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, _MinFilter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, _MagFilter);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Index, 0, _InternalFormat, _Width, _Height, 0, _Format, _Type, Buffer);

		if (GenerateMipMaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	VOID CubeMap::Bind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _Texture);
	}

	VOID CubeMap::Mount(U32 const Index) const
	{
		glBindTextureUnit(Index, _Texture);
	}

	VOID CubeMap::Unmount(U32 const Index) const
	{
		glBindTextureUnit(Index, 0);
	}

	VOID CubeMap::Unbind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}