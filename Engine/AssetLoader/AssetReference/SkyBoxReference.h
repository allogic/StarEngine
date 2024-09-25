#pragma once

namespace StarEngine
{
	class SkyBoxReference : public AssetReference
	{
	public:

		SkyBoxReference();

		virtual ~SkyBoxReference();

	public:

		inline SkyBox const* GetSkyBox() const { return _SkyBox; }

	public:

		VOID Reload() override;

	private:

		SkyBox* _SkyBox = nullptr;
	};
}