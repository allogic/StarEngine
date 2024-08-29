#include <Engine/PreCompiled.h>

#define STB_IMAGE_IMPLEMENTATION

	#include <Engine/StbImage/stb_image.h>

#undef STB_IMAGE_IMPLEMENTATION

#define STB_IMAGE_WRITE_IMPLEMENTATION

	#include <Engine/StbImage/stb_image_write.h>

#undef STB_IMAGE_WRITE_IMPLEMENTATION

#include <Engine/Utility/FileSystem.h>

namespace StarEngine::FileSystem
{
	VOID ReadBinaryFile(fs::path const& FilePath, std::vector<U8>& Buffer, U64 Size)
	{
		std::ifstream stream(FilePath, std::ios::ate | std::ios::binary);

		if (stream.is_open())
		{
			if (Size == 0)
			{
				Size = stream.tellg();
			}
			else
			{
				Size = std::min(Size, (U64)stream.tellg());
			}

			Buffer.resize(Size);

			stream.seekg(std::ios::beg);

			if (Size)
			{
				stream.read((CHAR*)Buffer.data(), Size);
			}

			stream.close();
		}
	}

	VOID ReadTextFile(fs::path const& FilePath, std::string& Text, U64 Size)
	{
		std::ifstream stream(FilePath, std::ios::ate);

		if (stream.is_open())
		{
			if (Size == 0)
			{
				Size = stream.tellg();
			}
			else
			{
				Size = std::min(Size, (U64)stream.tellg());
			}

			Text.resize(Size);

			stream.seekg(std::ios::beg);

			if (Size)
			{
				stream.read(Text.data(), Size);
			}

			stream.close();
		}
	}

	VOID WriteBinaryFile(fs::path const& FilePath, std::vector<U8> const& Buffer, U64 Size)
	{
		std::ofstream stream(FilePath, std::ios::binary);

		if (stream.is_open())
		{
			if (Size == 0)
			{
				Size = Buffer.size();
			}
			else
			{
				Size = std::min(Size, (U64)Buffer.size());
			}

			if (Size)
			{
				stream.write((CHAR const*)Buffer.data(), Size);
			}

			stream.close();
		}
	}

	VOID WriteBinaryFile(fs::path const& FilePath, U8 const* Buffer, U64 Size)
	{
		std::ofstream stream(FilePath, std::ios::binary);

		if (stream.is_open())
		{
			stream.write((CHAR const*)Buffer, Size);
			stream.close();
		}
	}

	VOID WriteTextFile(fs::path const& FilePath, std::string const& Text, U64 Size)
	{
		std::ofstream stream(FilePath);

		if (stream.is_open())
		{
			if (Size == 0)
			{
				Size = Text.size();
			}
			else
			{
				Size = std::min(Size, (U64)Text.size());
			}

			if (Size)
			{
				stream.write(Text.data(), Size);
			}

			stream.close();
		}
	}

	VOID WriteTextFile(fs::path const& FilePath, U8 const* Text, U64 Size)
	{
		std::ofstream stream(FilePath);

		if (stream.is_open())
		{
			stream.write((CHAR const*)Text, Size);
			stream.close();
		}
	}

	VOID ReadImageFile(fs::path const& FilePath, std::vector<U8>& Buffer, U32& Width, U32& Height, U32& Channels)
	{
		U8* RawBuffer = stbi_load(FilePath.string().data(), (I32*)&Width, (I32*)&Height, (I32*)&Channels, 0);

		U64 Size = (U64)Width * Height * Channels;

		Buffer.resize(Size);

		std::memcpy(Buffer.data(), RawBuffer, Size);

		stbi_image_free(RawBuffer);
	}

	VOID WriteImageFile(U32 Width, U32 Height, std::vector<U8> const& Buffer, fs::path const& FilePath)
	{
		stbi_write_png(FilePath.string().data(), Width, Height, 1, Buffer.data(), Width);
	}
}