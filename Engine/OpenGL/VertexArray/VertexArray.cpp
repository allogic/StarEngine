#include <Engine/PreCompiled.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/VertexArray/VertexArray.h>

namespace StarEngine
{
	VertexArray::VertexArray(VertexType const Type)
	{
		glGenVertexArrays(1, &_Vao);

		glGenBuffers(1, &_Vbo);
		glGenBuffers(1, &_Ebo);

		glBindVertexArray(_Vao);

		glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Ebo);

		switch (Type)
		{
			case VertexType::VERTEX_TYPE_PRINCIPLED_BRDF_GEOMETRY:
			{
				using Vertex = PrincipledBRDFGeometryVertex;

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);
				glEnableVertexAttribArray(3);
				glEnableVertexAttribArray(4);
				glEnableVertexAttribArray(5);

				glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(0));
				glVertexAttribPointer(1, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(offsetof(Vertex, Normal)));
				glVertexAttribPointer(2, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(offsetof(Vertex, Tangent)));
				glVertexAttribPointer(3, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(offsetof(Vertex, Bitangent)));
				glVertexAttribPointer(4, 2, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(offsetof(Vertex, TextureCoords)));
				glVertexAttribIPointer(5, 1, GL_UNSIGNED_INT, sizeof(Vertex), (VOID*)(offsetof(Vertex, Color)));

				break;
			}
			case VertexType::VERTEX_TYPE_PRINCIPLED_BRDF_LIGHTING:
			{
				using Vertex = PrincipledBRDFLightingVertex;

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(0));
				glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(offsetof(Vertex, TextureCoords)));

				break;
			}
			case VertexType::VERTEX_TYPE_POST_PROCESS:
			{
				using Vertex = PostProcessVertex;

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(0));
				glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(offsetof(Vertex, TextureCoords)));

				break;
			}
			case VertexType::VERTEX_TYPE_GIZMO_LINE:
			{
				using Vertex = GizmoLineVertex;

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(0));
				glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(Vertex), (VOID*)(offsetof(Vertex, Color)));

				break;
			}
			case VertexType::VERTEX_TYPE_GIZMO_QUAD:
			{
				using Vertex = GizmoQuadVertex;

				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);

				glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(0));
				glVertexAttribPointer(1, 2, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(offsetof(Vertex, TextureCoords)));
				glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(Vertex), (VOID*)(offsetof(Vertex, Color)));

				break;
			}
			case VertexType::VERTEX_TYPE_SKYBOX:
			{
				using Vertex = SkyBoxVertex;

				glEnableVertexAttribArray(0);

				glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(Vertex), (VOID*)(0));

				break;
			}
		}

		glBindVertexArray(0);
	}

	VertexArray::~VertexArray()
	{
		glGenBuffers(1, &_Vbo);
		glGenBuffers(1, &_Ebo);

		glGenVertexArrays(1, &_Vao);
	}

	VOID VertexArray::Bind() const
	{
		glBindVertexArray(_Vao);
	}

	VOID VertexArray::Draw(RenderMode const Mode) const
	{
		switch (Mode)
		{
			case RenderMode::RENDER_MODE_LINES: glDrawElements(GL_LINES, (I32)_IndexBufferCount, GL_UNSIGNED_INT, nullptr); break;
			case RenderMode::RENDER_MODE_TRIANGLES: glDrawElements(GL_TRIANGLES, (I32)_IndexBufferCount, GL_UNSIGNED_INT, nullptr); break;
		}
	}

	VOID VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	VOID VertexArray::GetVertices(VOID* VertexBuffer, U64 VertexStructSize, U64 VertexBufferCount)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, VertexStructSize * VertexBufferCount, VertexBuffer);
	}

	VOID VertexArray::GetIndices(VOID* IndexBuffer, U64 IndexStructSize, U64 IndexBufferCount)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Ebo);
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, IndexStructSize * IndexBufferCount, IndexBuffer);
	}

	VOID VertexArray::SetVertices(VOID* VertexBuffer, U64 VertexStructSize, U64 VertexBufferCount)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
		glBufferData(GL_ARRAY_BUFFER, VertexStructSize * VertexBufferCount, VertexBuffer, GL_STATIC_READ | GL_STATIC_DRAW);

		_VertexBufferCount = VertexBufferCount;
	}

	VOID VertexArray::SetIndices(VOID* IndexBuffer, U64 IndexStructSize, U64 IndexBufferCount)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexStructSize * IndexBufferCount, IndexBuffer, GL_STATIC_READ | GL_STATIC_DRAW);

		_IndexBufferCount = IndexBufferCount;
	}
}