#include <Engine/PreCompiled.h>
#include <Engine/Memory.h>

namespace StarEngine
{
	static U64 m_Allocated = 0;

	VOID* Memory::Alloc(U64 Size, VOID* Reference)
	{
		U64 NewSize = sizeof(U64) + Size;

		U64* NewBlock = (U64*)std::calloc(1, NewSize);

		m_Allocated += NewSize;

		*NewBlock = NewSize;
		NewBlock += 1;

		if (Reference)
		{
			std::memcpy(NewBlock, Reference, Size);
		}

		return NewBlock;
	}

	VOID* Memory::Realloc(VOID* Block, U64 Size)
	{
		U64* PrevBlock = (U64*)Block;

		PrevBlock -= 1;

		U64 PrevSize = *PrevBlock;
		U64 NewSize = sizeof(U64) + Size;

		m_Allocated -= PrevSize;

		U64* NewBlock = (U64*)std::realloc(PrevBlock, NewSize);

		if (NewSize > PrevSize)
		{
			std::memset(((UCHAR*)NewBlock) + PrevSize, 0, NewSize - PrevSize);
		}

		m_Allocated += NewSize;

		*NewBlock = NewSize;
		NewBlock += 1;

		return NewBlock;
	}

	VOID Memory::Free(VOID* Block)
	{
		U64* PrevBlock = (U64*)Block;

		PrevBlock -= 1;

		U64 PrevSize = *PrevBlock;

		m_Allocated -= PrevSize;

		std::free(PrevBlock);
	}

#ifdef SE_DEBUG

	VOID Memory::CheckForLeaks()
	{
		assert(m_Allocated == 0);
	}

#endif // SE_DEBUG

}