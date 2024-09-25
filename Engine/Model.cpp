#include <Engine/PreCompiled.h>
#include <Engine/Mesh.h>
#include <Engine/Model.h>

#include <Engine/OpenGL/Material/Material.h>

#include <Engine/OpenGL/Texture/Texture2D.h>

#include <Engine/Utility/FileSystem.h>
#include <Engine/Utility/MathUtility.h>
#include <Engine/Utility/PathUtility.h>
#include <Engine/Utility/StringUtility.h>

namespace StarEngine
{
	Model::Model()
	{
		
	}

	Model::~Model()
	{
		for (auto const [MeshName, Mesh] : _Meshes)
		{
			Mesh->~Mesh();

			Memory::Free(Mesh);
		}
	}

	BOOL Model::ContainsMeshWithName(std::string const& MeshName) const
	{
		return _Meshes.find(MeshName) == _Meshes.end();
	}

	VOID Model::SetMeshByName(std::string const& MeshName, Mesh* Mesh)
	{
		_Meshes[MeshName] = Mesh;
	}

	entt::entity Model::CreateEntity(entt::registry& Registry) const
	{
		entt::entity Entity = Registry.create();

		//CreateEntityRecursive(Registry, Entity, _Scene->mRootNode, glm::identity<R32M4>());

		return Entity;
	}

	VOID Model::CreateEntityRecursive(entt::registry& Registry, entt::entity const& ParentEntity, aiNode const* Node, R32M4 const& ParentTransform) const
	{
		//R32M4 LocalTransform = AssimpMatrixToR32M4(Node->mTransformation);
		//R32M4 WorldTransform = ParentTransform * LocalTransform;
		//
		//entt::entity Entity = Registry.create();
		//
		//TransformComponent& Transform = Registry.emplace<TransformComponent>(Entity);
		//
		//Transform.ParentEntity = ParentEntity;
		//
		//for (U32 MeshIndex = 0; MeshIndex < Node->mNumMeshes; MeshIndex++)
		//{
		//	aiMesh const* AssimpMesh = _Scene->mMeshes[Node->mMeshes[MeshIndex]];
		//
		//	CHAR const* MeshName = AssimpMesh->mName.C_Str();
		//
		//	entt::entity SubEntity = Registry.create();
		//
		//	TransformComponent& SubTransform = Registry.emplace<TransformComponent>(SubEntity);
		//	RenderComponent& SubRenderable = Registry.emplace<RenderComponent>(SubEntity);
		//
		//	SubTransform.ParentEntity = Entity;
		//
		//	R32V3 Position = {};
		//	R32V3 Rotation = {};
		//	R32V3 Scale = {};
		//
		//	MathUtility::DecomposeTransform(WorldTransform, Position, Rotation, Scale);
		//
		//	TransformSystem::SetPosition(Registry, SubTransform, Position);
		//	TransformSystem::SetRotation(Registry, SubTransform, Rotation);
		//	TransformSystem::SetScale(Registry, SubTransform, Scale);
		//
		//	auto MeshIter = _Meshes.find(MeshName);
		//
		//	if (MeshIter != _Meshes.end())
		//	{
		//		SubRenderable.Mesh = MeshIter->second;
		//	}
		//}
		//
		//for (U32 ChildIndex = 0; ChildIndex < Node->mNumChildren; ChildIndex++)
		//{
		//	CreateEntityRecursive(Registry, Entity, Node->mChildren[ChildIndex], WorldTransform);
		//}
	}
}