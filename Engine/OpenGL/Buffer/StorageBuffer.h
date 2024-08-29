#pragma once

namespace StarEngine
{
	class StorageBuffer
	{
	public:

		StorageBuffer(U64 const StructSize, U64 const BufferCount);

		virtual ~StorageBuffer();

	public:

		inline U32 GetBuffer() const { return _Buffer; }

	public:

		VOID Bind() const;
		VOID BeginBarrier() const;
		VOID SetBuffer(VOID const* Buffer) const;
		VOID SetBuffer(VOID const* Buffer, U64 const Offset, U64 const Count) const;
		VOID EndBarrier() const;
		VOID Mount(U32 Index) const;
		VOID Unmount(U32 const Index) const;
		VOID Unbind() const;

	private:

		U32 _Buffer = 0;

		U64 _StructSize = 0;
		U64 _BufferCount = 0;
	};
}