#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Buffer/UniformBuffer.h>

namespace StarEngine
{
	UniformBuffer::UniformBuffer(U64 const StructSize, U64 const BufferCount)
	{
		_StructSize = StructSize;
		_BufferCount = BufferCount;

		glGenBuffers(1, &_Buffer);

		glBindBuffer(GL_UNIFORM_BUFFER, _Buffer);
		glBufferData(GL_UNIFORM_BUFFER, _StructSize * _BufferCount, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &_Buffer);
	}

	VOID UniformBuffer::Bind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, _Buffer);
	}

	VOID UniformBuffer::BeginBarrier() const
	{
		glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
	}

	VOID UniformBuffer::SetBuffer(VOID const* Buffer) const
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, _StructSize * _BufferCount, (VOID*)Buffer);
	}

	VOID UniformBuffer::SetBuffer(VOID const* Buffer, U64 const Offset, U64 const Count) const
	{
		glBufferSubData(GL_UNIFORM_BUFFER, _StructSize * Offset, _StructSize * Count, (VOID*)Buffer);
	}

	VOID UniformBuffer::EndBarrier() const
	{
		glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
	}

	VOID UniformBuffer::Mount(U32 const Index) const
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, Index, _Buffer);
	}

	VOID UniformBuffer::Unmount(U32 const Index) const
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, Index, 0);
	}

	VOID UniformBuffer::Unbind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}