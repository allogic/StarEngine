#include <Engine/PreCompiled.h>

namespace StarEngine
{
	MaterialReference::MaterialReference()
		: AssetReference()
	{

	}

	MaterialReference::~MaterialReference()
	{

	}

	VOID MaterialReference::SetTextureReferenceByName(std::string const& TextureName, Texture2DReference const* Texture2DReference)
	{
		_Texture2DReferences[TextureName] = Texture2DReference;
	}

	VOID MaterialReference::SetTextureAttenuatorByName(std::string const& TextureName, R32 Attenuator)
	{
		_Texture2DAttenuators[TextureName] = Attenuator;
	}

	VOID MaterialReference::Reload()
	{

	}
}