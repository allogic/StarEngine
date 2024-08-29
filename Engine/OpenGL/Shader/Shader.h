#pragma once

namespace StarEngine
{
	class Shader
	{
	public:

		Shader();

		virtual ~Shader();

	public:

		VOID Load(fs::path const& VertexShaderFilePath, fs::path const& FragmentShaderFilePath);

	public:

		VOID Bind() const;
		VOID Unbind() const;

	public:

		VOID SetU32(std::string const& UniformName, U32 Integer) const;

		VOID SetR32(std::string const& UniformName, R32 Real) const;

		VOID SetR32V3(std::string const& UniformName, R32V3 const& Vector) const;

		VOID SetR32M4(std::string const& UniformName, R32M4 const& Matrix) const;

	private:

#ifdef SE_DEBUG

		static VOID CheckCompileStatus(U32 Shader);
		static VOID CheckLinkStatus(U32 Program);

#endif // SE_DEBUG

	private:

		U32 _Program;
	};
}