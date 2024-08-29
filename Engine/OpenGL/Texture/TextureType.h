#pragma once

namespace StarEngine
{
	enum TextureType : U32
	{
		TEXTURE_TYPE_NONE = 0,
		TEXTURE_TYPE_U8 = 0x1401,
		TEXTURE_TYPE_R32 = 0x1406,
		TEXTURE_TYPE_U24_U8 = 0x84FA,
	};
}