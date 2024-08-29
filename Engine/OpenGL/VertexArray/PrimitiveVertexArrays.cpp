#include <Engine/PreCompiled.h>

#include <Engine/OpenGL/VertexArray/PrimitiveVertexArrays.h>
#include <Engine/OpenGL/VertexArray/VertexArray.h>

namespace StarEngine::PrimitiveVertexArrays
{
	static VOID CreatePrincipledBRDFLightingQuad();
	static VOID CreatePostProcessQuad();
	static VOID CreateSkyBoxCube();

	static VertexArray* m_PrincipledBRDFLightingQuad = nullptr;
	static VertexArray* m_PostProcessQuad = nullptr;
	static VertexArray* m_SkyBoxCube = nullptr;

	VOID Create()
	{
		CreatePrincipledBRDFLightingQuad();
		CreatePostProcessQuad();
		CreateSkyBoxCube();
	}

	VOID Destroy()
	{
		m_PrincipledBRDFLightingQuad->~VertexArray();
		m_PostProcessQuad->~VertexArray();
		m_SkyBoxCube->~VertexArray();

		Memory::Free(m_PrincipledBRDFLightingQuad);
		Memory::Free(m_PostProcessQuad);
		Memory::Free(m_SkyBoxCube);
	}


	VertexArray* GetPrincipledBRDFLightingQuad()
	{
		return m_PrincipledBRDFLightingQuad;
	}

	VertexArray* GetPostProcessQuad()
	{
		return m_PostProcessQuad;
	}

	VertexArray* GetSkyBoxCube()
	{
		return m_SkyBoxCube;
	}

	static VOID CreatePrincipledBRDFLightingQuad()
	{
		m_PrincipledBRDFLightingQuad = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_PRINCIPLED_BRDF_LIGHTING);

		PrincipledBRDFLightingVertex Vertices[4] = {};
		U32 Indices[6] = {};

		Vertices[0].Position = R32V3(0.0F, 0.0F, 0.0F);
		Vertices[0].TextureCoords = R32V2(0.0F, 0.0F);

		Vertices[1].Position = R32V3(1.0F, 0.0F, 0.0F);
		Vertices[1].TextureCoords = R32V2(1.0F, 0.0F);

		Vertices[2].Position = R32V3(1.0F, 1.0F, 0.0F);
		Vertices[2].TextureCoords = R32V2(1.0F, 1.0F);

		Vertices[3].Position = R32V3(0.0F, 1.0F, 0.0F);
		Vertices[3].TextureCoords = R32V2(0.0F, 1.0F);

		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;

		Indices[3] = 2;
		Indices[4] = 3;
		Indices[5] = 0;

		m_PrincipledBRDFLightingQuad->Bind();
		m_PrincipledBRDFLightingQuad->SetVertices(Vertices, sizeof(PrincipledBRDFLightingVertex), 4);
		m_PrincipledBRDFLightingQuad->SetIndices(Indices, sizeof(U32), 6);
		m_PrincipledBRDFLightingQuad->Unbind();
	}

	static VOID CreatePostProcessQuad()
	{
		m_PostProcessQuad = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_POST_PROCESS);

		PostProcessVertex Vertices[4] = {};
		U32 Indices[6] = {};

		Vertices[0].Position = R32V3(0.0F, 0.0F, 0.0F);
		Vertices[0].TextureCoords = R32V2(0.0F, 0.0F);

		Vertices[1].Position = R32V3(1.0F, 0.0F, 0.0F);
		Vertices[1].TextureCoords = R32V2(1.0F, 0.0F);

		Vertices[2].Position = R32V3(1.0F, 1.0F, 0.0F);
		Vertices[2].TextureCoords = R32V2(1.0F, 1.0F);

		Vertices[3].Position = R32V3(0.0F, 1.0F, 0.0F);
		Vertices[3].TextureCoords = R32V2(0.0F, 1.0F);

		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;

		Indices[3] = 2;
		Indices[4] = 3;
		Indices[5] = 0;

		m_PostProcessQuad->Bind();
		m_PostProcessQuad->SetVertices(Vertices, sizeof(PostProcessVertex), 4);
		m_PostProcessQuad->SetIndices(Indices, sizeof(U32), 6);
		m_PostProcessQuad->Unbind();
	}

	static VOID CreateSkyBoxCube()
	{
		m_SkyBoxCube = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_SKYBOX);

		SkyBoxVertex Vertices[8] = {};
		U32 Indices[36] = {};

		Vertices[0].Position = R32V3(-1.0F, -1.0F, -1.0F);
		Vertices[1].Position = R32V3(1.0F, -1.0F, -1.0F);
		Vertices[2].Position = R32V3(1.0F, 1.0F, -1.0F);
		Vertices[3].Position = R32V3(-1.0F, 1.0F, -1.0F);

		Vertices[4].Position = R32V3(-1.0F, -1.0F, 1.0F);
		Vertices[5].Position = R32V3(1.0F, -1.0F, 1.0F);
		Vertices[6].Position = R32V3(1.0F, 1.0F, 1.0F);
		Vertices[7].Position = R32V3(-1.0F, 1.0F, 1.0F);

		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;

		Indices[3] = 2;
		Indices[4] = 3;
		Indices[5] = 0;

		Indices[6] = 4;
		Indices[7] = 6;
		Indices[8] = 5;

		Indices[9] = 6;
		Indices[10] = 4;
		Indices[11] = 7;

		Indices[12] = 0;
		Indices[13] = 4;
		Indices[14] = 1;

		Indices[15] = 4;
		Indices[16] = 5;
		Indices[17] = 1;

		Indices[18] = 1;
		Indices[19] = 5;
		Indices[20] = 6;

		Indices[21] = 1;
		Indices[22] = 6;
		Indices[23] = 2;

		Indices[24] = 0;
		Indices[25] = 7;
		Indices[26] = 4;

		Indices[27] = 3;
		Indices[28] = 7;
		Indices[29] = 0;

		Indices[30] = 2;
		Indices[31] = 6;
		Indices[32] = 3;

		Indices[33] = 3;
		Indices[34] = 6;
		Indices[35] = 7;

		m_SkyBoxCube->Bind();
		m_SkyBoxCube->SetVertices(Vertices, sizeof(SkyBoxVertex), 8);
		m_SkyBoxCube->SetIndices(Indices, sizeof(U32), 36);
		m_SkyBoxCube->Unbind();
	}
}