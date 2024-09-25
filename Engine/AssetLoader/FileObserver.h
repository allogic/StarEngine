#pragma once

namespace StarEngine
{
    class FileObserver
    {
    public:

        FileObserver(fs::path const& ObservableFilePath);

        virtual ~FileObserver();

    public:

        inline VOID RegisterCreateCallback(std::function<VOID()> const& CreateCallback) { _CreateCallback = CreateCallback; }
        inline VOID RegisterModifyCallback(std::function<VOID()> const& ModifyCallback) { _ModifyCallback = ModifyCallback; }
        inline VOID RegisterDeleteCallback(std::function<VOID()> const& DeleteCallback) { _DeleteCallback = DeleteCallback; }

    public:

        VOID Update();

    private:

        VOID CheckFileDeleted();
        VOID CheckFileModified();
        VOID CheckFileCreated();

    private:

        fs::path _ObservableFilePath = "";

        fs::file_time_type _LastWriteTime = {};

        std::function<VOID()> _CreateCallback = {};
        std::function<VOID()> _ModifyCallback = {};
        std::function<VOID()> _DeleteCallback = {};
    };
}