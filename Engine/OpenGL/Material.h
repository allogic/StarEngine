#pragma once

namespace StarEngine
{
	class Material
	{
	public:

		Material();

		virtual ~Material();

	public:

		inline std::string const& GetName() const { return _Name; }
		inline Shader* GetShader() const { return _Shader; }

		inline Texture2D* GetAlbedoTexture() const { return _AlbedoTexture; }
		inline Texture2D* GetNormalTexture() const { return _NormalTexture; }
		inline Texture2D* GetMetallicTexture() const { return _MetallicTexture; }
		inline Texture2D* GetRoughnessTexture() const { return _RoughnessTexture; }
		inline Texture2D* GetAmbientOcclusionTexture() const { return _AmbientOcclusionTexture; }
		inline Texture2D* GetHeightTexture() const { return _HeightTexture; }
		inline Texture2D* GetEmissiveTexture() const { return _EmissiveTexture; }
		inline Texture2D* GetOpacityTexture() const { return _OpacityTexture; }

		inline CubeMap* GetCubeMap() const { return _CubeMap; }

	public:

		inline VOID SetName(std::string const& Name) { _Name = Name; }
		inline VOID SetShader(Shader* Shader) { _Shader = Shader; }

	public:

		Texture2D* LoadAlbedoTexture(fs::path const& FilePath);
		Texture2D* LoadNormalTexture(fs::path const& FilePath);
		Texture2D* LoadMetallicTexture(fs::path const& FilePath);
		Texture2D* LoadRoughnessTexture(fs::path const& FilePath);
		Texture2D* LoadAmbientOcclusionTexture(fs::path const& FilePath);
		Texture2D* LoadHeightTexture(fs::path const& FilePath);
		Texture2D* LoadEmissiveTexture(fs::path const& FilePath);
		Texture2D* LoadOpacityTexture(fs::path const& FilePath);

		CubeMap* LoadCubeMap(fs::path const& FilePath);

	private:

		std::string _Name = "";

		Shader* _Shader = nullptr;

		Texture2D* _AlbedoTexture = nullptr;
		Texture2D* _NormalTexture = nullptr;
		Texture2D* _MetallicTexture = nullptr;
		Texture2D* _RoughnessTexture = nullptr;
		Texture2D* _AmbientOcclusionTexture = nullptr;
		Texture2D* _HeightTexture = nullptr;
		Texture2D* _EmissiveTexture = nullptr;
		Texture2D* _OpacityTexture = nullptr;

		CubeMap* _CubeMap = nullptr;
	};
}