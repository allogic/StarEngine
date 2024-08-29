#pragma once

#include <Engine/OpenGL/RenderModes.h>

#include <Engine/OpenGL/VertexArray/VertexTypes.h>

namespace StarEngine
{
	class VertexArray
	{
	public:

		VertexArray(VertexType const Type);

		virtual ~VertexArray();

	public:

		inline U64 GetVertexBufferCount() const { return _VertexBufferCount; }
		inline U64 GetIndexBufferCount() const { return _IndexBufferCount; }

	public:

		VOID Bind() const;
		VOID Draw(RenderMode const Mode) const;
		VOID Unbind() const;

	public:

		VOID GetVertices(VOID* VertexBuffer, U64 VertexStructSize, U64 VertexBufferCount);
		VOID GetIndices(VOID* IndexBuffer, U64 IndexStructSize, U64 IndexBufferCount);

		VOID SetVertices(VOID* VertexBuffer, U64 VertexStructSize, U64 VertexBufferCount);
		VOID SetIndices(VOID* IndexBuffer, U64 IndexStructSize, U64 IndexBufferCount);

	private:

		U32 _Vao = 0;
		U32 _Vbo = 0;
		U32 _Ebo = 0;

		U64 _VertexBufferCount = 0;
		U64 _IndexBufferCount = 0;
	};
}