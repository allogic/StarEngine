#pragma once

namespace StarEngine
{
	enum TextureInternalFormat : U32
	{
		TEXTURE_INTERNAL_FORMAT_NONE = 0,
		TEXTURE_INTERNAL_FORMAT_RGBA = 0x1908,
		TEXTURE_INTERNAL_FORMAT_RGB = 0x1907,
		TEXTURE_INTERNAL_FORMAT_RG = 0x8227,
		TEXTURE_INTERNAL_FORMAT_R = 0x1903,
		TEXTURE_INTERNAL_FORMAT_R_U8 = 0x8232,
		TEXTURE_INTERNAL_FORMAT_R_R32 = 0x822E,
		TEXTURE_INTERNAL_FORMAT_RGB_U8 = 0x8D7D,
		TEXTURE_INTERNAL_FORMAT_RGB_R32 = 0x8815,
		TEXTURE_INTERNAL_FORMAT_RGBA_U8 = 0x8D7C,
		TEXTURE_INTERNAL_FORMAT_RGBA_R32 = 0x8814,
		TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8 = 0x88F0,
	};
}