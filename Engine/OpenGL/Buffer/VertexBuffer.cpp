#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Buffer/VertexBuffer.h>

namespace StarEngine
{
	VertexBuffer::VertexBuffer(U64 const StructSize, U64 const BufferCount)
	{
		_StructSize = StructSize;
		_BufferCount = BufferCount;

		glGenBuffers(1, &_Buffer);

		glBindBuffer(GL_ARRAY_BUFFER, _Buffer);
		glBufferData(GL_ARRAY_BUFFER, _StructSize * _BufferCount, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &_Buffer);
	}

	VOID VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _Buffer);
	}

	VOID VertexBuffer::BeginBarrier() const
	{
		glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
	}

	VOID VertexBuffer::SetBuffer(VOID const* Buffer) const
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, _StructSize * _BufferCount, (VOID*)Buffer);
	}

	VOID VertexBuffer::SetBuffer(VOID const* Buffer, U64 const Offset, U64 const Count) const
	{
		glBufferSubData(GL_ARRAY_BUFFER, _StructSize * Offset, _StructSize * Count, (VOID*)Buffer);
	}

	VOID VertexBuffer::EndBarrier() const
	{
		glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
	}

	VOID VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}