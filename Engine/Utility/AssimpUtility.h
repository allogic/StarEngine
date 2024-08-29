#pragma once

namespace StarEngine::AssimpUtility
{
	aiNode const* FindNodeByNameRecursive(aiNode const* Node, std::string const& Name);
}