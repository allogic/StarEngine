#pragma once

namespace StarEngine
{
	class Memory
	{
	public:

		static VOID* Alloc(U64 Size, VOID* Reference = nullptr);
		static VOID* Realloc(VOID* Block, U64 Size);

		static VOID Free(VOID* Block);

#ifdef SE_DEBUG

		static VOID CheckForLeaks();

#endif // SE_DEBUG

	};
}