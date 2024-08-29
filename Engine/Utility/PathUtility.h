#pragma once

namespace StarEngine::PathUtility
{
	fs::path ResolveRelativeFilePath(fs::path const& RootPath, fs::path const& RelativePath);
}