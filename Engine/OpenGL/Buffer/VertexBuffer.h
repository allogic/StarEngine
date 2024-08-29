#pragma once

namespace StarEngine
{
	class VertexBuffer
	{
	public:

		VertexBuffer(U64 const StructSize, U64 const BufferCount);

		virtual ~VertexBuffer();

	public:

		inline U32 GetBuffer() const { return _Buffer; }

	public:

		VOID Bind() const;
		VOID BeginBarrier() const;
		VOID SetBuffer(VOID const* Buffer) const;
		VOID SetBuffer(VOID const* Buffer, U64 const Offset, U64 const Count) const;
		VOID EndBarrier() const;
		VOID Unbind() const;

	private:

		U32 _Buffer = 0;

		U64 _StructSize = 0;
		U64 _BufferCount = 0;
	};
}