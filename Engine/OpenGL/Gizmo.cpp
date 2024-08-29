#include <Engine/PreCompiled.h>

#include <Engine/OpenGL/Gizmo.h>

#include <Engine/OpenGL/Shader/Shader.h>
#include <Engine/OpenGL/Shader/ShaderRegistry.h>

#include <Engine/OpenGL/VertexArray/VertexArray.h>

namespace StarEngine::Gizmo
{
	constexpr U64 LINE_BATCH_VERTEX_BUFFER_COUNT = 0x10000;
	constexpr U64 LINE_BATCH_INDEX_BUFFER_COUNT = 0x20000;

	constexpr U64 QUAD_BATCH_VERTEX_BUFFER_COUNT = 0x10000;
	constexpr U64 QUAD_BATCH_INDEX_BUFFER_COUNT = 0x60000;

	static Shader* m_LineShader = nullptr;
	static Shader* m_QuadShader = nullptr;

	static Shader* m_LineBatchShader = nullptr;
	static Shader* m_QuadBatchShader = nullptr;

	static VertexArray* m_LineVertexArray = nullptr;
	static VertexArray* m_QuadVertexArray = nullptr;

	static VertexArray* m_LineBatchVertexArray = nullptr;
	static VertexArray* m_QuadBatchVertexArray = nullptr;

	static GizmoLineVertex* m_VertexLineBatchBuffer;
	static GizmoQuadVertex* m_VertexQuadBatchBuffer;

	static U32* m_IndexLineBatchBuffer;
	static U32* m_IndexQuadBatchBuffer;

	static U32 m_LineBatchVertexOffset, m_QuadBatchVertexOffset;
	static U32 m_LineBatchIndexOffset, m_QuadBatchIndexOffset;

	VOID Create()
	{
		m_LineShader = ShaderRegistry::GetShaderByName("Gizmo/Line");
		m_QuadShader = ShaderRegistry::GetShaderByName("Gizmo/Quad");

		m_LineBatchShader = ShaderRegistry::GetShaderByName("Gizmo/LineBatch");
		m_QuadBatchShader = ShaderRegistry::GetShaderByName("Gizmo/QuadBatch");

		m_LineVertexArray = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_GIZMO_LINE);
		m_QuadVertexArray = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_GIZMO_QUAD);

		m_LineBatchVertexArray = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_GIZMO_LINE);
		m_QuadBatchVertexArray = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_GIZMO_QUAD);

		m_VertexLineBatchBuffer = (GizmoLineVertex*)Memory::Alloc(LINE_BATCH_VERTEX_BUFFER_COUNT, 0);
		m_VertexQuadBatchBuffer = (GizmoQuadVertex*)Memory::Alloc(QUAD_BATCH_VERTEX_BUFFER_COUNT, 0);

		m_IndexLineBatchBuffer = (U32*)Memory::Alloc(LINE_BATCH_INDEX_BUFFER_COUNT, 0);
		m_IndexQuadBatchBuffer = (U32*)Memory::Alloc(QUAD_BATCH_INDEX_BUFFER_COUNT, 0);
	}

	VOID Destroy()
	{
		m_LineVertexArray->~VertexArray();
		m_QuadVertexArray->~VertexArray();

		m_LineBatchVertexArray->~VertexArray();
		m_QuadBatchVertexArray->~VertexArray();

		Memory::Free(m_VertexLineBatchBuffer);
		Memory::Free(m_VertexQuadBatchBuffer);

		Memory::Free(m_IndexLineBatchBuffer);
		Memory::Free(m_IndexQuadBatchBuffer);

		Memory::Free(m_LineVertexArray);
		Memory::Free(m_QuadVertexArray);

		Memory::Free(m_LineBatchVertexArray);
		Memory::Free(m_QuadBatchVertexArray);
	}

	VOID BeginLines(R32M4 const& Projection, R32M4 const& View, R32M4 const& Model)
	{
		m_LineShader->Bind();

		m_LineShader->SetR32M4("Projection", Projection);
		m_LineShader->SetR32M4("View", View);
		m_LineShader->SetR32M4("Model", Model);
	}

	VOID DrawLine(R32V3 const& From, R32V3 const& To, U32 Color)
	{
		static GizmoLineVertex VertexBuffer[2];
		static U32 IndexBuffer[2];

		VertexBuffer[0].Position.x = From.x;
		VertexBuffer[0].Position.y = From.y;
		VertexBuffer[0].Position.z = From.z;
		VertexBuffer[0].Color = Color;

		VertexBuffer[1].Position.x = To.x;
		VertexBuffer[1].Position.y = To.y;
		VertexBuffer[1].Position.z = To.z;
		VertexBuffer[1].Color = Color;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;

		m_LineVertexArray->Bind();
		m_LineVertexArray->SetVertices(VertexBuffer, sizeof(GizmoLineVertex), 2);
		m_LineVertexArray->SetIndices(IndexBuffer, sizeof(U32), 2);
		m_LineVertexArray->Draw(RenderMode::RENDER_MODE_LINES);
		m_LineVertexArray->Unbind();
	}

	VOID EndLines()
	{
		m_LineShader->Unbind();
	}

	VOID BeginQuads(R32M4 const& Projection, R32M4 const& View, R32M4 const& Model)
	{
		m_QuadShader->Bind();

		m_QuadShader->SetR32M4("Projection", Projection);
		m_QuadShader->SetR32M4("View", View);
		m_QuadShader->SetR32M4("Model", Model);
	}

	VOID DrawQuad(R32V3 const& Position, R32V2 const& Size, U32 Color)
	{
		static GizmoQuadVertex VertexBuffer[4];
		static U32 IndexBuffer[6];

		VertexBuffer[0].Position.x = Position.x;
		VertexBuffer[0].Position.y = Position.y;
		VertexBuffer[0].Position.z = Position.z;
		VertexBuffer[0].TextureCoords[0] = 0.0F;
		VertexBuffer[0].TextureCoords[1] = 0.0F;
		VertexBuffer[0].Color = Color;

		VertexBuffer[1].Position.x = Position.x + Size.x;
		VertexBuffer[1].Position.y = Position.y;
		VertexBuffer[1].Position.z = Position.z;
		VertexBuffer[1].TextureCoords[0] = 1.0F;
		VertexBuffer[1].TextureCoords[1] = 0.0F;
		VertexBuffer[1].Color = Color;

		VertexBuffer[2].Position.x = Position.x + Size.x;
		VertexBuffer[2].Position.y = Position.y + Size.y;
		VertexBuffer[2].Position.z = Position.z;
		VertexBuffer[2].TextureCoords[0] = 1.0F;
		VertexBuffer[2].TextureCoords[1] = 1.0F;
		VertexBuffer[2].Color = Color;

		VertexBuffer[3].Position.x = Position.x;
		VertexBuffer[3].Position.y = Position.y + Size.y;
		VertexBuffer[3].Position.z = Position.z;
		VertexBuffer[3].TextureCoords[0] = 0.0F;
		VertexBuffer[3].TextureCoords[1] = 1.0F;
		VertexBuffer[3].Color = Color;

		IndexBuffer[0] = 0;
		IndexBuffer[1] = 1;
		IndexBuffer[2] = 2;

		IndexBuffer[3] = 2;
		IndexBuffer[4] = 3;
		IndexBuffer[5] = 0;

		m_QuadVertexArray->Bind();
		m_QuadVertexArray->SetVertices(VertexBuffer, sizeof(GizmoQuadVertex), 4);
		m_QuadVertexArray->SetIndices(IndexBuffer, sizeof(U32), 6);
		m_QuadVertexArray->Draw(RenderMode::RENDER_MODE_TRIANGLES);
		m_QuadVertexArray->Unbind();
	}

	VOID EndQuads()
	{
		m_QuadShader->Unbind();
	}

	VOID BeginLineBatch(R32M4 const& Projection, R32M4 const& View)
	{
		m_LineBatchShader->Bind();

		m_LineBatchShader->SetR32M4("Projection", Projection);
		m_LineBatchShader->SetR32M4("View", View);
	}

	VOID PushBatchLine(R32V3 const& From, R32V3 const& To, U32 Color)
	{
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Position.x = From.x;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Position.y = From.y;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Position.z = From.z;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Color = Color;

		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Position.x = To.x;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Position.y = To.y;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Position.z = To.z;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Color = Color;

		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 0] = m_LineBatchVertexOffset + 0;
		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 1] = m_LineBatchVertexOffset + 1;

		m_LineBatchVertexOffset += 2;
		m_LineBatchIndexOffset += 2;
	}

	VOID PushBatchLineGrid(R32V3 const& Position, U32 NumOfLines, R32 Scale, U32 Color, R32Q const& Rotation)
	{
		U32 IndexOffset = 0;

		R32 SizeStep = Scale / NumOfLines;
		R32 HalfSize = Scale / 2;

		for (U32 LineIndex = 0; LineIndex <= NumOfLines; LineIndex++)
		{
			R32 GridOffset = (R32)LineIndex * SizeStep - HalfSize;

			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 0].Position = Position + Rotation * R32V3{ GridOffset, 0.0F, -HalfSize };
			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 1].Position = Position + Rotation * R32V3{ GridOffset, 0.0F, HalfSize };
			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 2].Position = Position + Rotation * R32V3{ -HalfSize, 0.0F, GridOffset };
			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 3].Position = Position + Rotation * R32V3{ HalfSize, 0.0F, GridOffset };

			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 0].Color = Color;
			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 1].Color = Color;
			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 2].Color = Color;
			m_VertexLineBatchBuffer[m_LineBatchVertexOffset + IndexOffset + 3].Color = Color;

			m_IndexLineBatchBuffer[m_LineBatchIndexOffset + IndexOffset + 0] = m_LineBatchVertexOffset + IndexOffset + 0;
			m_IndexLineBatchBuffer[m_LineBatchIndexOffset + IndexOffset + 1] = m_LineBatchVertexOffset + IndexOffset + 1;
			m_IndexLineBatchBuffer[m_LineBatchIndexOffset + IndexOffset + 2] = m_LineBatchVertexOffset + IndexOffset + 2;
			m_IndexLineBatchBuffer[m_LineBatchIndexOffset + IndexOffset + 3] = m_LineBatchVertexOffset + IndexOffset + 3;

			IndexOffset += 4;
		}

		m_LineBatchVertexOffset += IndexOffset;
		m_LineBatchIndexOffset += IndexOffset;
	}

	VOID PushBatchLineRect(R32V3 const& Position, R32V2 const& Size, U32 Color)
	{
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Position.x = Position.x;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Position.y = Position.y;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Position.z = Position.z;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 0].Color = Color;

		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Position.x = Position.x + Size.x;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Position.y = Position.y;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Position.z = Position.z;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 1].Color = Color;

		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 2].Position.x = Position.x + Size.x;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 2].Position.y = Position.y + Size.y;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 2].Position.z = Position.z;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 2].Color = Color;

		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 3].Position.x = Position.x;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 3].Position.y = Position.y + Size.y;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 3].Position.z = Position.z;
		m_VertexLineBatchBuffer[m_LineBatchVertexOffset + 3].Color = Color;

		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 0] = m_LineBatchVertexOffset + 0;
		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 1] = m_LineBatchVertexOffset + 1;

		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 2] = m_LineBatchVertexOffset + 1;
		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 3] = m_LineBatchVertexOffset + 2;

		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 4] = m_LineBatchVertexOffset + 2;
		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 5] = m_LineBatchVertexOffset + 3;

		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 6] = m_LineBatchVertexOffset + 3;
		m_IndexLineBatchBuffer[m_LineBatchIndexOffset + 7] = m_LineBatchVertexOffset + 0;

		m_LineBatchVertexOffset += 4;
		m_LineBatchIndexOffset += 8;
	}

	VOID DrawLineBatch()
	{
		m_LineBatchVertexArray->Bind();
		m_LineBatchVertexArray->SetVertices(m_VertexLineBatchBuffer, sizeof(GizmoLineVertex), m_LineBatchVertexOffset);
		m_LineBatchVertexArray->SetIndices(m_IndexLineBatchBuffer, sizeof(U32), m_LineBatchIndexOffset);
		m_LineBatchVertexArray->Draw(RenderMode::RENDER_MODE_LINES);
		m_LineBatchVertexArray->Unbind();

		m_LineBatchVertexOffset = 0;
		m_LineBatchIndexOffset = 0;
	}

	VOID EndLineBatch()
	{
		m_LineBatchShader->Unbind();
	}

	VOID BeginQuadBatch(R32M4 const& Projection, R32M4 const& View)
	{
		m_QuadBatchShader->Bind();

		m_QuadBatchShader->SetR32M4("Projection", Projection);
		m_QuadBatchShader->SetR32M4("View", View);
	}

	VOID PushBatchQuad(R32V3 const& Position, R32V2 const& Size, U32 Color)
	{
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 0].Position.x = Position.x;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 0].Position.y = Position.y;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 0].Position.z = Position.z;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 0].TextureCoords[0] = 0.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 0].TextureCoords[1] = 0.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 0].Color = Color;

		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 1].Position.x = Position.x + Size.x;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 1].Position.y = Position.y;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 1].Position.z = Position.z;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 1].TextureCoords[0] = 1.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 1].TextureCoords[1] = 0.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 1].Color = Color;

		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 2].Position.x = Position.x + Size.x;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 2].Position.y = Position.y + Size.y;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 2].Position.z = Position.z;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 2].TextureCoords[0] = 1.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 2].TextureCoords[1] = 1.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 2].Color = Color;

		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 3].Position.x = Position.x;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 3].Position.y = Position.y + Size.y;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 3].Position.z = Position.z;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 3].TextureCoords[0] = 0.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 3].TextureCoords[1] = 1.0F;
		m_VertexQuadBatchBuffer[m_QuadBatchVertexOffset + 3].Color = Color;

		m_IndexQuadBatchBuffer[m_QuadBatchIndexOffset + 0] = m_QuadBatchVertexOffset + 0;
		m_IndexQuadBatchBuffer[m_QuadBatchIndexOffset + 1] = m_QuadBatchVertexOffset + 1;
		m_IndexQuadBatchBuffer[m_QuadBatchIndexOffset + 2] = m_QuadBatchVertexOffset + 2;

		m_IndexQuadBatchBuffer[m_QuadBatchIndexOffset + 3] = m_QuadBatchVertexOffset + 2;
		m_IndexQuadBatchBuffer[m_QuadBatchIndexOffset + 4] = m_QuadBatchVertexOffset + 3;
		m_IndexQuadBatchBuffer[m_QuadBatchIndexOffset + 5] = m_QuadBatchVertexOffset + 0;

		m_QuadBatchVertexOffset += 4;
		m_QuadBatchIndexOffset += 6;
	}

	VOID DrawQuadBatch()
	{
		m_QuadBatchVertexArray->Bind();
		m_QuadBatchVertexArray->SetVertices(m_VertexQuadBatchBuffer, sizeof(GizmoQuadVertex), m_QuadBatchVertexOffset);
		m_QuadBatchVertexArray->SetIndices(m_IndexQuadBatchBuffer, sizeof(U32), m_QuadBatchIndexOffset);
		m_QuadBatchVertexArray->Draw(RenderMode::RENDER_MODE_TRIANGLES);
		m_QuadBatchVertexArray->Unbind();

		m_QuadBatchVertexOffset = 0;
		m_QuadBatchIndexOffset = 0;
	}

	VOID EndQuadBatch()
	{
		m_QuadBatchShader->Unbind();
	}
}