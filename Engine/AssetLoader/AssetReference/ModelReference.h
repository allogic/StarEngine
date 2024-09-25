#pragma once

namespace StarEngine
{
	class ModelReference : public AssetReference
	{
	public:

		ModelReference();

		virtual ~ModelReference();

	public:

		inline Model const* GetModel() const { return _Model; }

	public:

		inline VOID SetModelFilePath(fs::path const& ModelFilePath) { _ModelFilePath = ModelFilePath; }

	public:

		VOID Reload() override;

	private:

		Model* _Model = nullptr;

		fs::path _ModelFilePath = "";
	};
}