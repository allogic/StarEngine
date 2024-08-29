#include <Engine/PreCompiled.h>

#include <Engine/Utility/StringUtility.h>

namespace StarEngine::StringUtility
{
	std::string ReplaceCharacter(std::string const& String, CHAR OldCharacter, CHAR NewCharacter)
	{
		std::string Result = String;

		std::replace(Result.begin(), Result.end(), OldCharacter, NewCharacter);

		return Result;
	}
}