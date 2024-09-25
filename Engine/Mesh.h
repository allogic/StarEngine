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

		inline MaterialReference const* GetMaterialReference() const { return _MaterialReference; }

		inline VertexArray* GetVertexArray() const { return _VertexArray; }

	public:

		inline VOID SetName(std::string const& Name) { _Name = Name; }

		inline VOID SetMaterialReference(MaterialReference const* MaterialReference) { _MaterialReference = MaterialReference; }

		inline VOID SetVertexArray(VertexArray* VertexArray) { _VertexArray = VertexArray; }

	private:

		std::string _Name = "";

		MaterialReference const* _MaterialReference = nullptr;

		VertexArray* _VertexArray = nullptr;
	};
}