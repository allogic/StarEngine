#pragma once

namespace StarEngine
{
	class Model
	{
	private:

		struct AsyncImageResource
		{
			BOOL Loaded = false;

			U32 Width = 0;
			U32 Height = 0;
			U32 Channels = 0;

			std::vector<U8> Buffer = {};
		};

	public:

		Model();

		virtual ~Model();

	public:

		VOID Load(fs::path const& FilePath);

	public:

		entt::entity CreateEntity(entt::registry& Registry) const;

	private:

		VOID CreateEntityRecursive(entt::registry& Registry, entt::entity const& ParentEntity, aiNode const* Node, R32M4 const& ParentTransform) const;

	private:

		VOID LoadMeshes();

	private:

		Assimp::Importer* _Importer = nullptr;

		aiScene const* _Scene = nullptr;

		fs::path _FilePath = "";

		std::string _FileName = "";

		std::vector<std::future<AsyncImageResource>> _AsyncImageResources = {};

		std::map<std::string, Material*> _Materials = {};
		std::map<std::string, Mesh*> _Meshes = {};
	};
}