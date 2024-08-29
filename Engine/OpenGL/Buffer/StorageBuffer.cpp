#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Buffer/StorageBuffer.h>

namespace StarEngine
{
	StorageBuffer::StorageBuffer(U64 const StructSize, U64 const BufferCount)
	{
		_StructSize = StructSize;
		_BufferCount = BufferCount;

		glGenBuffers(1, &_Buffer);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _Buffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, _StructSize * _BufferCount, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	StorageBuffer::~StorageBuffer()
	{
		glDeleteBuffers(1, &_Buffer);
	}

	VOID StorageBuffer::Bind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _Buffer);
	}

	VOID StorageBuffer::BeginBarrier() const
	{
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}

	VOID StorageBuffer::SetBuffer(VOID const* Buffer) const
	{
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, _StructSize * _BufferCount, (VOID*)Buffer);
	}

	VOID StorageBuffer::SetBuffer(VOID const* Buffer, U64 const Offset, U64 const Count) const
	{
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, _StructSize * Offset, _StructSize * Count, (VOID*)Buffer);
	}

	VOID StorageBuffer::EndBarrier() const
	{
		glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);
	}

	VOID StorageBuffer::Mount(U32 const Index) const
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Index, _Buffer);
	}

	VOID StorageBuffer::Unmount(U32 const Index) const
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Index, 0);
	}

	VOID StorageBuffer::Unbind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
}