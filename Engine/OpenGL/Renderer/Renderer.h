#pragma once

namespace StarEngine::Renderer
{
	VOID Create(U32 const Width, U32 const Height);
	VOID Destroy();

	VOID Resize(U32 const Width, U32 const Height);

	VOID Draw(entt::registry const& Registry, R32 const AspectRatio);
}