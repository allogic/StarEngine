#include <Engine/PreCompiled.h>

#include <Engine/Utility/PathUtility.h>

namespace StarEngine::PathUtility
{
	fs::path ResolveRelativeFilePath(fs::path const& RootPath, fs::path const& RelativePath)
	{
		if (fs::exists(RootPath / RelativePath))
		{
			if (fs::is_regular_file(RootPath / RelativePath))
			{
				return RootPath / RelativePath;
			}
		}
		else
		{
			auto OuterIter = RelativePath.begin();

			while (OuterIter != RelativePath.end())
			{
				fs::path Path = RootPath;

				for (auto InnerIter = OuterIter; InnerIter != RelativePath.end(); InnerIter++)
				{
					Path /= *InnerIter;

					if (fs::exists(Path))
					{
						if (fs::is_regular_file(Path))
						{
							return Path;
						}
					}
				}

				OuterIter++;
			}
		}

		return "";
	}
}