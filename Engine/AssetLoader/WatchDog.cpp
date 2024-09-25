#include <Engine/PreCompiled.h>

#include <Engine/AssetLoader/WatchDog.h>

namespace StarEngine
{
	WatchDog::WatchDog(fs::path const& ObservableFilePath, std::string const& FileExtension)
	{
		_ObservableFilePath = ObservableFilePath;
		_FileExtension = FileExtension;

		std::filesystem::create_directory(ObservableFilePath);
	}

	WatchDog::~WatchDog()
	{

	}

	VOID WatchDog::Update()
	{
		CheckFilesDeleted();
		CheckFilesModified();
		CheckFilesCreated();
	}

	VOID WatchDog::CheckFilesDeleted()
	{
		_FilesDeleted.clear();

		std::erase_if(_FileInfos, [&](auto const& FileInfo)
			{
				fs::path const& FilePath = FileInfo.first;

				BOOL Exist = fs::exists(FilePath);

				if (!Exist)
				{
					_FilesDeleted.emplace(FilePath);
				}

				return !Exist;
			});
	}

	VOID WatchDog::CheckFilesModified()
	{
		_FilesModified.clear();

		for (auto& [FilePath, LastWriteTime] : _FileInfos)
		{
			fs::file_time_type WriteTime = fs::last_write_time(FilePath);

			if (WriteTime > LastWriteTime)
			{
				LastWriteTime = WriteTime;

				_FilesModified.emplace(FilePath);
			}
		}
	}

	VOID WatchDog::CheckFilesCreated()
	{
		_FilesCreated.clear();

		for (auto const& File : fs::recursive_directory_iterator(_ObservableFilePath))
		{
			fs::path FilePath = File.path();
			std::string FileExtension = FilePath.extension().string();
			fs::file_time_type WriteTime = fs::last_write_time(FilePath);

			if (FileExtension == _FileExtension)
			{
				if (_FileInfos.find(FilePath) == _FileInfos.end())
				{
					_FileInfos.emplace(FilePath, WriteTime);
					_FilesCreated.emplace(FilePath);
				}
			}
		}
	}
}