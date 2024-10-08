#include <Engine/PreCompiled.h>
#include <Engine/Mesh.h>

#include <Engine/OpenGL/VertexArray/VertexArray.h>

namespace StarEngine
{
	Mesh::Mesh()
	{

	}

	Mesh::~Mesh()
	{
		_VertexArray->~VertexArray();

		Memory::Free(_VertexArray);
	}
}