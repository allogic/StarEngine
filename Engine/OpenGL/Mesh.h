#pragma once

namespace StarEngine
{
	class Mesh
	{
	public:

		Mesh();

		virtual ~Mesh();

	public:

		inline std::string const& GetName() const { return _Name; }

		inline VertexArray* GetVertexArray() const { return _VertexArray; }
		inline Material* GetMaterial() const { return _Material; }

	public:

		inline VOID SetName(std::string const& Name) { _Name = Name; }

		inline VOID SetVertexArray(VertexArray* VertexArray) { _VertexArray = VertexArray; }
		inline VOID SetMaterial(Material* Material) { _Material = Material; }

	private:

		std::string _Name = "";

		VertexArray* _VertexArray = nullptr;
		Material* _Material = nullptr;
	};
}