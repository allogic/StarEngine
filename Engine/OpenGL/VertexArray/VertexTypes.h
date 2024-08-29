#pragma once

namespace StarEngine
{
	enum VertexType : U32
	{
		VERTEX_TYPE_NONE = 0,

		VERTEX_TYPE_PRINCIPLED_BRDF_GEOMETRY,
		VERTEX_TYPE_PRINCIPLED_BRDF_LIGHTING,

		VERTEX_TYPE_POST_PROCESS,

		VERTEX_TYPE_GIZMO_LINE,
		VERTEX_TYPE_GIZMO_QUAD,

		VERTEX_TYPE_SKYBOX,
	};

	struct PrincipledBRDFGeometryVertex
	{
		R32V3 Position;
		R32V3 Normal;
		R32V3 Tangent;
		R32V3 Bitangent;
		R32V2 TextureCoords;

		U32 Color;
	};

	struct PrincipledBRDFLightingVertex
	{
		R32V3 Position;
		R32V2 TextureCoords;
	};

	struct PostProcessVertex
	{
		R32V3 Position;
		R32V2 TextureCoords;
	};

	struct GizmoLineVertex
	{
		R32V3 Position;

		U32 Color;
	};

	struct GizmoQuadVertex
	{
		R32V3 Position;
		R32V2 TextureCoords;

		U32 Color;
	};

	struct SkyBoxVertex
	{
		R32V3 Position;
	};
}