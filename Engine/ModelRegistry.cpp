#include <Engine/PreCompiled.h>
#include <Engine/Model.h>
#include <Engine/ModelRegistry.h>

namespace StarEngine::ModelRegistry
{
	static std::map<std::string, Model*> m_Models = {};

	VOID Create(fs::path const& ModelFilePath)
	{
		Model* Cockpit = AddModel("Cockpit");

		Cockpit->Load(ModelFilePath / "Cockpit" / "Cockpit.fbx");
	}

	VOID Destroy()
	{
		RemoveModel("Cockpit");
	}

	Model* GetModelByName(std::string const& ModelName)
	{
		if (m_Models.find(ModelName) != m_Models.end())
		{
			return m_Models[ModelName];
		}

		return nullptr;
	}

	Model* AddModel(std::string const& ModelName)
	{
		if (m_Models.find(ModelName) == m_Models.end())
		{
			return m_Models[ModelName] = new (Memory::Alloc(sizeof(Model))) Model;
		}

		return nullptr;
	}

	VOID RemoveModel(std::string const& ModelName)
	{
		auto Iter = m_Models.find(ModelName);

		if (Iter != m_Models.end())
		{
			Model* Model = Iter->second;

			Model->~Model();

			Memory::Free(Model);

			m_Models.erase(Iter);
		}
	}
}