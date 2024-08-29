#pragma once

namespace StarEngine::FileSystem
{
	VOID ReadBinaryFile(fs::path const& FilePath, std::vector<U8>& Buffer, U64 Size = 0);
	VOID ReadTextFile(fs::path const& FilePath, std::string& Text, U64 Size = 0);

	VOID WriteBinaryFile(fs::path const& FilePath, std::vector<U8> const& Buffer, U64 Size = 0);
	VOID WriteBinaryFile(fs::path const& FilePath, U8 const* Buffer, U64 Size);

	VOID WriteTextFile(fs::path const& FilePath, std::string const& Text, U64 Size = 0);
	VOID WriteTextFile(fs::path const& FilePath, U8 const* Text, U64 Size);

	VOID ReadImageFile(fs::path const& FilePath, std::vector<U8>& Buffer, U32& Width, U32& Height, U32& Channels);
	VOID WriteImageFile(U32 Width, U32 Height, std::vector<U8> const& Buffer, fs::path const& FilePath);
}