#pragma once

namespace StarEngine
{
	class AssetReference
	{
	public:

		AssetReference();

		virtual ~AssetReference();

	public:

		virtual VOID Reload() = 0;

	private:

		std::vector<AssetReference*> _References = {};
		std::vector<FileObserver*> _Observers = {};
	};
}