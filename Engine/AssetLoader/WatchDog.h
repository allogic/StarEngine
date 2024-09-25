#pragma once

namespace StarEngine
{
    class WatchDog
    {
    public:

        WatchDog(fs::path const& ObservableFilePath, std::string const& FileExtension);

        virtual ~WatchDog();

    public:

        inline std::set<fs::path> const& GetFilesCreated() const { return _FilesCreated; }
        inline std::set<fs::path> const& GetFilesDeleted() const { return _FilesDeleted; }
        inline std::set<fs::path> const& GetFilesModified() const { return _FilesModified; }

    public:

        VOID Update();

    private:

        VOID CheckFilesDeleted();
        VOID CheckFilesModified();
        VOID CheckFilesCreated();

    private:

        fs::path _ObservableFilePath = "";

        std::string _FileExtension = "";

        std::map<fs::path, fs::file_time_type> _FileInfos = {};

        std::set<fs::path> _FilesCreated = {};
        std::set<fs::path> _FilesDeleted = {};
        std::set<fs::path> _FilesModified = {};
    };
}