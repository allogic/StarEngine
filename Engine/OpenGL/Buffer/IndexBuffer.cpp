#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Buffer/IndexBuffer.h>

namespace StarEngine
{
	IndexBuffer::IndexBuffer(U64 const StructSize, U64 const BufferCount)
	{
		_StructSize = StructSize;
		_BufferCount = BufferCount;

		glGenBuffers(1, &_Buffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _StructSize * _BufferCount, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &_Buffer);
	}

	VOID IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Buffer);
	}

	VOID IndexBuffer::BeginBarrier() const
	{
		glMemoryBarrier(GL_ELEMENT_ARRAY_BARRIER_BIT);
	}

	VOID IndexBuffer::SetBuffer(VOID const* Buffer) const
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _StructSize * _BufferCount, (VOID*)Buffer);
	}

	VOID IndexBuffer::SetBuffer(VOID const* Buffer, U64 const Offset, U64 const Count) const
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _StructSize * Offset, _StructSize * Count, (VOID*)Buffer);
	}

	VOID IndexBuffer::EndBarrier() const
	{
		glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
	}

	VOID IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}