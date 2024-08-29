#pragma once

namespace StarEngine::Gizmo
{
	VOID Create();
	VOID Destroy();

	VOID BeginLines(R32M4 const& Projection, R32M4 const& View, R32M4 const& Model);
	VOID DrawLine(R32V3 const& From, R32V3 const& To, U32 Color);
	VOID EndLines();

	VOID BeginQuads(R32M4 const& Projection, R32M4 const& View, R32M4 const& Model);
	VOID DrawQuad(R32V3 const& Position, R32V2 const& Size, U32 Color);
	VOID EndQuads();

	VOID BeginLineBatch(R32M4 const& Projection, R32M4 const& View);
	VOID PushBatchLine(R32V3 const& From, R32V3 const& To, U32 Color);
	VOID PushBatchLineRect(R32V3 const& Position, R32V2 const& Size, U32 Color);
	VOID PushBatchLineGrid(R32V3 const& Position, U32 NumOfLines, R32 Scale, U32 Color, R32Q const& Rotation = {});
	VOID DrawLineBatch();
	VOID EndLineBatch();

	VOID BeginQuadBatch(R32M4 const& Projection, R32M4 const& View);
	VOID PushBatchQuad(R32V3 const& Position, R32V2 const& Size, U32 Color);
	VOID DrawQuadBatch();
	VOID EndQuadBatch();
}