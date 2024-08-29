#include <Engine/PreCompiled.h>
#include <Engine/Model.h>

#include <Engine/Assimp/Importer.hpp>
#include <Engine/Assimp/Exporter.hpp>
#include <Engine/Assimp/postprocess.h>
#include <Engine/Assimp/scene.h>

#include <Engine/OpenGL/Material.h>
#include <Engine/OpenGL/MaterialRegistry.h>
#include <Engine/OpenGL/Mesh.h>

#include <Engine/OpenGL/Shader/ShaderRegistry.h>

#include <Engine/OpenGL/Texture/Texture2D.h>

#include <Engine/OpenGL/VertexArray/VertexArray.h>

#include <Engine/Utility/FileSystem.h>
#include <Engine/Utility/MathUtility.h>
#include <Engine/Utility/PathUtility.h>
#include <Engine/Utility/StringUtility.h>

namespace StarEngine
{
	static R32M4 AssimpMatrixToR32M4(aiMatrix4x4 const& Matrix);
	static R32V3 AssimpVectorToR32V3(aiVector3D const& Vector);
	static R32V4 AssimpColorToR32V4(aiColor4D const& Color);
	static R32Q AssimpQuaternionToR32Q(aiQuaternion const& Orientation);

	Model::Model()
	{
		
	}

	Model::~Model()
	{
		for (auto const [MaterialName, Material] : _Materials)
		{
			Material->~Material();

			Memory::Free(Material);
		}

		for (auto const [MeshName, Mesh] : _Meshes)
		{
			Mesh->~Mesh();

			Memory::Free(Mesh);
		}

		_Importer->~Importer();

		Memory::Free(_Importer);
	}

	VOID Model::Load(fs::path const& FilePath)
	{
		_Importer = new (Memory::Alloc(sizeof(Assimp::Importer))) Assimp::Importer;
		_FilePath = FilePath;
		_FileName = FilePath.stem().string();

		U32 importFlags = aiProcess_ValidateDataStructure | aiProcess_GenSmoothNormals | aiProcess_LimitBoneWeights | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_PopulateArmatureData;

		_Scene = _Importer->ReadFile(_FilePath.string(), importFlags);

		if (_Scene && (_Scene->mFlags & ~(AI_SCENE_FLAGS_INCOMPLETE)) && _Scene->mRootNode)
		{
			LoadMeshes();
		}
	}

	entt::entity Model::CreateEntity(entt::registry& Registry) const
	{
		entt::entity Entity = Registry.create();

		CreateEntityRecursive(Registry, Entity, _Scene->mRootNode, glm::identity<R32M4>());

		return Entity;
	}

	VOID Model::CreateEntityRecursive(entt::registry& Registry, entt::entity const& ParentEntity, aiNode const* Node, R32M4 const& ParentTransform) const
	{
		R32M4 LocalTransform = AssimpMatrixToR32M4(Node->mTransformation);
		R32M4 WorldTransform = ParentTransform * LocalTransform;

		entt::entity Entity = Registry.create();

		TransformComponent& Transform = Registry.emplace<TransformComponent>(Entity);

		Transform.ParentEntity = ParentEntity;

		for (U32 MeshIndex = 0; MeshIndex < Node->mNumMeshes; MeshIndex++)
		{
			aiMesh const* AssimpMesh = _Scene->mMeshes[Node->mMeshes[MeshIndex]];

			CHAR const* MeshName = AssimpMesh->mName.C_Str();

			entt::entity SubEntity = Registry.create();

			TransformComponent& SubTransform = Registry.emplace<TransformComponent>(SubEntity);
			RenderComponent& SubRenderable = Registry.emplace<RenderComponent>(SubEntity);

			SubTransform.ParentEntity = Entity;

			R32V3 Position = {};
			R32V3 Rotation = {};
			R32V3 Scale = {};

			MathUtility::DecomposeTransform(WorldTransform, Position, Rotation, Scale);

			TransformSystem::SetPosition(Registry, SubTransform, Position);
			TransformSystem::SetRotation(Registry, SubTransform, Rotation);
			TransformSystem::SetScale(Registry, SubTransform, Scale);

			auto MeshIter = _Meshes.find(MeshName);

			if (MeshIter != _Meshes.end())
			{
				SubRenderable.Mesh = MeshIter->second;
			}
		}

		for (U32 ChildIndex = 0; ChildIndex < Node->mNumChildren; ChildIndex++)
		{
			CreateEntityRecursive(Registry, Entity, Node->mChildren[ChildIndex], WorldTransform);
		}
	}

	VOID Model::LoadMeshes()
	{
		for (U32 MeshIndex = 0; MeshIndex < _Scene->mNumMeshes; MeshIndex++)
		{
			aiMesh const* AssimpMesh = _Scene->mMeshes[MeshIndex];

			std::vector<PrincipledBRDFGeometryVertex> Vertices = {};
			std::vector<U32> Indices = {};

			Vertices.resize(AssimpMesh->mNumVertices);
			Indices.resize(AssimpMesh->mNumFaces * 3);

			BOOL FoundTangentsAndBitangents = false;

			for (U32 VertexIndex = 0; VertexIndex < AssimpMesh->mNumVertices; VertexIndex++)
			{
				if (AssimpMesh->HasPositions())
				{
					Vertices[VertexIndex].Position = AssimpVectorToR32V3(AssimpMesh->mVertices[VertexIndex]);
				}

				if (AssimpMesh->HasNormals())
				{
					Vertices[VertexIndex].Normal = AssimpVectorToR32V3(AssimpMesh->mNormals[VertexIndex]);
				}

				if (AssimpMesh->GetNumUVChannels() > 0)
				{
					Vertices[VertexIndex].TextureCoords = AssimpVectorToR32V3(AssimpMesh->mTextureCoords[0][VertexIndex]);
				}

				if (AssimpMesh->HasTangentsAndBitangents())
				{
					FoundTangentsAndBitangents = true;

					Vertices[VertexIndex].Tangent = AssimpVectorToR32V3(AssimpMesh->mTangents[VertexIndex]);
					Vertices[VertexIndex].Bitangent = AssimpVectorToR32V3(AssimpMesh->mBitangents[VertexIndex]);
				}

				if (AssimpMesh->GetNumColorChannels() > 0)
				{
					R32V4 Color = AssimpColorToR32V4(AssimpMesh->mColors[0][VertexIndex]);

					U32 R = (U32)(Color.r * 255.0F);
					U32 G = (U32)(Color.g * 255.0F);
					U32 B = (U32)(Color.b * 255.0F);
					U32 A = (U32)(Color.a * 255.0F);

					Vertices[VertexIndex].Color = ((R & 0xFF) << 24) | ((G & 0xFF) << 16) | ((B & 0xFF) << 8) | (A & 0xFF);
				}
			}

			for (U32 FaceIndex = 0, IndicesIndex = 0; FaceIndex < AssimpMesh->mNumFaces; FaceIndex++, IndicesIndex += 3)
			{
				aiFace const AssimpFace = AssimpMesh->mFaces[FaceIndex];

				U32 IA = AssimpFace.mIndices[0];
				U32 IB = AssimpFace.mIndices[1];
				U32 IC = AssimpFace.mIndices[2];

				Indices[IndicesIndex + 0] = IA;
				Indices[IndicesIndex + 1] = IB;
				Indices[IndicesIndex + 2] = IC;

				if (!FoundTangentsAndBitangents)
				{
					PrincipledBRDFGeometryVertex& VA = Vertices[IA];
					PrincipledBRDFGeometryVertex& VB = Vertices[IB];
					PrincipledBRDFGeometryVertex& VC = Vertices[IC];

					R32V3 EdgeA = VB.Position - VA.Position;
					R32V3 EdgeB = VC.Position - VA.Position;

					R32V2 DeltaUVA = VB.TextureCoords - VA.TextureCoords;
					R32V2 DeltaUVB = VC.TextureCoords - VA.TextureCoords;

					R32 F = 1.0F / ((DeltaUVA.x * DeltaUVB.y) - (DeltaUVB.x * DeltaUVA.y));

					R32 TX = F * ((DeltaUVB.y * EdgeA.x) - (DeltaUVA.y * EdgeB.x));
					R32 TY = F * ((DeltaUVB.y * EdgeA.y) - (DeltaUVA.y * EdgeB.y));
					R32 TZ = F * ((DeltaUVB.y * EdgeA.z) - (DeltaUVA.y * EdgeB.z));

					R32 BTX = F * ((-DeltaUVB.x * EdgeA.x) + (DeltaUVA.x * EdgeB.x));
					R32 BTY = F * ((-DeltaUVB.x * EdgeA.y) + (DeltaUVA.x * EdgeB.y));
					R32 BTZ = F * ((-DeltaUVB.x * EdgeA.z) + (DeltaUVA.x * EdgeB.z));

					R32V3 Tangent = glm::normalize(R32V3{ TX, TY, TZ });
					R32V3 Bitangent = glm::normalize(R32V3{ BTX, BTY, BTZ });

					VA.Tangent = Tangent;
					VA.Bitangent = Bitangent;

					VB.Tangent = Tangent;
					VB.Bitangent = Bitangent;

					VC.Tangent = Tangent;
					VC.Bitangent = Bitangent;
				}
			}

			VertexArray* DefaultVertexArray = new (Memory::Alloc(sizeof(VertexArray))) VertexArray(VertexType::VERTEX_TYPE_PRINCIPLED_BRDF_GEOMETRY);

			DefaultVertexArray->Bind();
			DefaultVertexArray->SetVertices(Vertices.data(), sizeof(PrincipledBRDFGeometryVertex), Vertices.size());
			DefaultVertexArray->SetIndices(Indices.data(), sizeof(U32), Indices.size());
			DefaultVertexArray->Unbind();

			CHAR const* MeshName = AssimpMesh->mName.C_Str();
			CHAR const* MaterialName = _Scene->mMaterials[AssimpMesh->mMaterialIndex]->GetName().C_Str();

			if (_Meshes.find(MeshName) == _Meshes.end())
			{
				Mesh* DefaultMesh = new (Memory::Alloc(sizeof(Mesh))) Mesh;

				DefaultMesh->SetName(MeshName);
				DefaultMesh->SetVertexArray(DefaultVertexArray);
				DefaultMesh->SetMaterial(MaterialRegistry::GetMaterialByName(_FileName + "/" + MaterialName));

				_Meshes[MeshName] = DefaultMesh;
			}
			else
			{
				DefaultVertexArray->~VertexArray();

				Memory::Free(DefaultVertexArray);
			}
		}
	}

	static R32M4 AssimpMatrixToR32M4(aiMatrix4x4 const& Matrix)
	{
		R32M4 Result = {};

		Result[0][0] = Matrix.a1; Result[1][0] = Matrix.a2; Result[2][0] = Matrix.a3; Result[3][0] = Matrix.a4;
		Result[0][1] = Matrix.b1; Result[1][1] = Matrix.b2; Result[2][1] = Matrix.b3; Result[3][1] = Matrix.b4;
		Result[0][2] = Matrix.c1; Result[1][2] = Matrix.c2; Result[2][2] = Matrix.c3; Result[3][2] = Matrix.c4;
		Result[0][3] = Matrix.d1; Result[1][3] = Matrix.d2; Result[2][3] = Matrix.d3; Result[3][3] = Matrix.d4;

		return Result;
	}

	static R32V3 AssimpVectorToR32V3(aiVector3D const& Vector)
	{
		return R32V3{ Vector.x, Vector.y, Vector.z };
	}

	static R32V4 AssimpColorToR32V4(aiColor4D const& Color)
	{
		return R32V4{ Color.r, Color.g, Color.b, Color.a };
	}

	static R32Q AssimpQuaternionToR32Q(aiQuaternion const& Orientation)
	{
		return R32Q{ Orientation.w, Orientation.x, Orientation.y, Orientation.z };
	}
}