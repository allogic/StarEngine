#include <Engine/PreCompiled.h>

#include <Engine/Assimp/scene.h>

#include <Engine/Utility/AssimpUtility.h>

namespace StarEngine::AssimpUtility
{
	aiNode const* FindNodeByNameRecursive(aiNode const* Node, std::string const& Name)
	{
		if (std::strcmp(Name.data(), Node->mName.C_Str()) == 0)
		{
			return Node;
		}

		for (U32 ChildIndex = 0; ChildIndex < Node->mNumChildren; ChildIndex++)
		{
			aiNode const* ChildNode = FindNodeByNameRecursive(Node->mChildren[ChildIndex], Name);

			if (ChildNode)
			{
				return ChildNode;
			}
		}

		return nullptr;
	}
}