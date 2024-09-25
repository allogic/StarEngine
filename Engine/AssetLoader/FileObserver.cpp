#include <Engine/PreCompiled.h>

#include <Engine/AssetLoader/FileObserver.h>

namespace StarEngine
{
	FileObserver::FileObserver(fs::path const& ObservableFilePath)
	{
		_ObservableFilePath = ObservableFilePath;
	}

	FileObserver::~FileObserver()
	{

	}

	VOID FileObserver::Update()
	{
		CheckFileDeleted();
		CheckFileModified();
		CheckFileCreated();
	}

	VOID FileObserver::CheckFileDeleted()
	{
		BOOL Exist = fs::exists(_ObservableFilePath);

		if (!Exist)
		{
			_LastWriteTime = {};

			_DeleteCallback();
		}
	}

	VOID FileObserver::CheckFileModified()
	{
		BOOL Exist = fs::exists(_ObservableFilePath);

		if (Exist)
		{
			fs::file_time_type WriteTime = fs::last_write_time(_ObservableFilePath);

			if (WriteTime > _LastWriteTime)
			{
				_LastWriteTime = WriteTime;

				_ModifyCallback();
			}
		}
	}

	VOID FileObserver::CheckFileCreated()
	{
		BOOL Exist = fs::exists(_ObservableFilePath);

		if (Exist)
		{
			_LastWriteTime = fs::last_write_time(_ObservableFilePath);

			_CreateCallback();
		}
	}
}