#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Shader/Shader.h>

#include <Engine/Utility/FileSystem.h>

namespace StarEngine
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{
		glDeleteProgram(_Program);
	}

	VOID Shader::Load(fs::path const& VertexShaderFilePath, fs::path const& FragmentShaderFilePath)
	{
		_Program = glCreateProgram();

		U32 VertexShader = glCreateShader(GL_VERTEX_SHADER);
		U32 FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexSource;
		std::string FragmentSource;

		FileSystem::ReadTextFile(VertexShaderFilePath, VertexSource);
		FileSystem::ReadTextFile(FragmentShaderFilePath, FragmentSource);

		CHAR const* VertexSourcePtr = VertexSource.data();
		CHAR const* FragmentSourcePtr = FragmentSource.data();

		glShaderSource(VertexShader, 1, &VertexSourcePtr, 0);
		glCompileShader(VertexShader);

#ifdef SE_DEBUG

		CheckCompileStatus(VertexShader);

#endif // SE_DEBUG

		glShaderSource(FragmentShader, 1, &FragmentSourcePtr, 0);
		glCompileShader(FragmentShader);

#ifdef SE_DEBUG

		CheckCompileStatus(FragmentShader);

#endif // SE_DEBUG

		glAttachShader(_Program, VertexShader);
		glAttachShader(_Program, FragmentShader);

		glLinkProgram(_Program);

#ifdef SE_DEBUG

		CheckLinkStatus(_Program);

#endif // SE_DEBUG

		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);
	}

	VOID Shader::Bind() const
	{
		glUseProgram(_Program);
	}

	VOID Shader::Unbind() const
	{
		glUseProgram(0);
	}

	VOID Shader::SetU32(std::string const& UniformName, U32 Integer) const
	{
		I32 Location = glGetUniformLocation(_Program, UniformName.data());

		glUniform1ui(Location, Integer);
	}

	VOID Shader::SetR32(std::string const& UniformName, R32 Real) const
	{
		I32 Location = glGetUniformLocation(_Program, UniformName.data());

		glUniform1f(Location, Real);
	}

	VOID Shader::SetR32V3(std::string const& UniformName, R32V3 const& Vector) const
	{
		I32 Location = glGetUniformLocation(_Program, UniformName.data());

		glUniform3fv(Location, 1, &Vector[0]);
	}

	VOID Shader::SetR32M4(std::string const& UniformName, R32M4 const& Matrix) const
	{
		I32 Location = glGetUniformLocation(_Program, UniformName.data());

		glUniformMatrix4fv(Location, 1, 0, &Matrix[0][0]);
	}

#ifdef SE_DEBUG

	VOID Shader::CheckCompileStatus(U32 Shader)
	{
		I32 CompileStatus = 0;
		I32 InfoLogLength = 0;

		static CHAR Log[0x400] = { 0 };

		glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompileStatus);

		if (CompileStatus == 0)
		{
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);

			if (InfoLogLength > 0)
			{
				InfoLogLength = std::min(InfoLogLength, (I32)sizeof(Log));

				glGetShaderInfoLog(Shader, InfoLogLength, &InfoLogLength, Log);

				std::printf(Log);
			}
		}
	}

	VOID Shader::CheckLinkStatus(U32 Program)
	{
		I32 CompileStatus = 0;
		I32 InfoLogLength = 0;

		static CHAR Log[0x400] = { 0 };

		glGetProgramiv(Program, GL_LINK_STATUS, &CompileStatus);

		if (CompileStatus == 0)
		{
			glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);

			if (InfoLogLength > 0)
			{
				InfoLogLength = std::min(InfoLogLength, (I32)sizeof(Log));

				glGetProgramInfoLog(Program, InfoLogLength, &InfoLogLength, &Log[0]);

				std::printf(Log);
			}
		}
	}

#endif // SE_DEBUG

}