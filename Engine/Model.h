#pragma once

namespace StarEngine
{
	class Model
	{
	public:

		Model();

		virtual ~Model();

	public:

		BOOL ContainsMeshWithName(std::string const& MeshName) const;
		VOID SetMeshByName(std::string const& MeshName, Mesh* Mesh);

	public:

		entt::entity CreateEntity(entt::registry& Registry) const;

	private:

		VOID CreateEntityRecursive(entt::registry& Registry, entt::entity const& ParentEntity, aiNode const* Node, R32M4 const& ParentTransform) const;

	private:

		std::map<std::string, Mesh*> _Meshes = {};
	};
}