#pragma once

namespace StarEngine::PrimitiveVertexArrays
{
	VOID Create();
	VOID Destroy();

	VertexArray* GetPrincipledBRDFLightingQuad();
	VertexArray* GetPostProcessQuad();
	VertexArray* GetSkyBoxCube();
}