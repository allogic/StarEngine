#pragma once

namespace StarEngine
{
	class SkyBoxMaterial : public Material
	{
	public:

		SkyBoxMaterial();

		virtual ~SkyBoxMaterial();

	public:

		inline std::string const& GetFrontTextureName() const { return _FrontTextureName; }
		inline std::string const& GetBackTextureName() const { return _BackTextureName; }
		inline std::string const& GetLeftTextureName() const { return _LeftTextureName; }
		inline std::string const& GetRightTextureName() const { return _RightTextureName; }
		inline std::string const& GetTopTextureName() const { return _TopTextureName; }
		inline std::string const& GetBottomTextureName() const { return _BottomTextureName; }

	private:

		std::string _FrontTextureName = "";
		std::string _BackTextureName = "";
		std::string _LeftTextureName = "";
		std::string _RightTextureName = "";
		std::string _TopTextureName = "";
		std::string _BottomTextureName = "";
	};
}