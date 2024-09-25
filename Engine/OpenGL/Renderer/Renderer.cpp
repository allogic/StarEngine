#include <Engine/PreCompiled.h>
#include <Engine/Mesh.h>

#include <Engine/GLAD/glad.h>

#include <Engine/OpenGL/Gizmo.h>

#include <Engine/OpenGL/Buffer/StorageBuffer.h>

#include <Engine/OpenGL/FrameBuffer/DefaultFrameBuffer.h>
#include <Engine/OpenGL/FrameBuffer/DeferredGeometryFrameBuffer.h>
#include <Engine/OpenGL/FrameBuffer/DeferredLightingFrameBuffer.h>

#include <Engine/OpenGL/Material/Material.h>
#include <Engine/OpenGL/Material/PrincipledBRDFMaterial.h>
#include <Engine/OpenGL/Material/SkyBoxMaterial.h>

#include <Engine/OpenGL/Renderer/LightTypes.h>
#include <Engine/OpenGL/Renderer/Renderer.h>

#include <Engine/OpenGL/Shader/Shader.h>

#include <Engine/OpenGL/Texture/CubeMap.h>
#include <Engine/OpenGL/Texture/Texture2D.h>

#include <Engine/OpenGL/VertexArray/VertexArray.h>
#include <Engine/OpenGL/VertexArray/PrimitiveVertexArrays.h>

namespace StarEngine::Renderer
{
	static constexpr U64 NUM_OF_POINT_LIGHTS = 64;

	static VOID ClearDefaultFrameBuffer();

	static VOID DeferredGeometryPass(entt::registry const& Registry);
	static VOID DeferredLightingPass(entt::registry const& Registry, R32V3 const& CameraPosition);

	static VOID CopyDeferredGeometryDepthIntoDefaultFrameBuffer(TextureFilter const& Filter);
	static VOID CopyDeferredLightingColorIntoDefaultFrameBuffer(TextureFilter const& Filter);

	static VOID SkyBoxPass();

	static VOID PostProcessPass();

	static R32M4 m_Projection = {};
	static R32M4 m_View = {};
	static R32M4 m_Model = {};

	static ShaderReference const* m_DeferredGeometryShaderReference = nullptr;
	static ShaderReference const* m_DeferredLightingShaderReference = nullptr;
	static ShaderReference const* m_SpaceBoxShaderReference = nullptr;
	static ShaderReference const* m_PassThroughShaderReference = nullptr;

	static U32 m_Width = 0;
	static U32 m_Height = 0;

	static StorageBuffer* m_PointLightBuffer = nullptr;

	static DefaultFrameBuffer* m_DefaultFrameBuffer = nullptr;
	static DeferredGeometryFrameBuffer* m_DeferredGeometryFrameBuffer = nullptr;
	static DeferredLightingFrameBuffer* m_DeferredLightingFrameBuffer = nullptr;

	VOID Create(U32 const Width, U32 const Height)
	{
		m_DeferredGeometryShaderReference = AssetLoader::GetShaderByName("DeferredGeometry");
		m_DeferredLightingShaderReference = AssetLoader::GetShaderByName("DeferredLighting");
		m_SpaceBoxShaderReference = AssetLoader::GetShaderByName("SpaceBox");
		m_PassThroughShaderReference = AssetLoader::GetShaderByName("PassThrough");

		m_Width = Width;
		m_Height = Height;

		m_PointLightBuffer = new (Memory::Alloc(sizeof(StorageBuffer))) StorageBuffer(sizeof(PointLight), NUM_OF_POINT_LIGHTS);

		m_DefaultFrameBuffer = new (Memory::Alloc(sizeof(DefaultFrameBuffer))) DefaultFrameBuffer(Width, Height);
		m_DeferredGeometryFrameBuffer = new (Memory::Alloc(sizeof(DeferredGeometryFrameBuffer))) DeferredGeometryFrameBuffer(Width, Height);
		m_DeferredLightingFrameBuffer = new (Memory::Alloc(sizeof(DeferredLightingFrameBuffer))) DeferredLightingFrameBuffer(Width, Height);
	}

	VOID Destroy()
	{
		m_PointLightBuffer->~StorageBuffer();

		m_DefaultFrameBuffer->~DefaultFrameBuffer();
		m_DeferredGeometryFrameBuffer->~DeferredGeometryFrameBuffer();
		m_DeferredLightingFrameBuffer->~DeferredLightingFrameBuffer();

		Memory::Free(m_PointLightBuffer);

		Memory::Free(m_DefaultFrameBuffer);
		Memory::Free(m_DeferredGeometryFrameBuffer);
		Memory::Free(m_DeferredLightingFrameBuffer);
	}

	VOID Resize(U32 const Width, U32 const Height)
	{
		m_Width = Width;
		m_Height = Height;

		m_DefaultFrameBuffer->Resize(m_Width, m_Height);
		m_DeferredGeometryFrameBuffer->Resize(m_Width, m_Height);
		m_DeferredLightingFrameBuffer->Resize(m_Width, m_Height);
	}

	VOID Draw(entt::registry const& Registry, R32 const AspectRatio)
	{
		auto const View = Registry.view<TransformComponent, CameraComponent, ShipControllerComponent>();

		for (auto const Entity : View)
		{
			auto const& Transform = Registry.get<TransformComponent>(Entity);
			auto const& Camera = Registry.get<CameraComponent>(Entity);
			auto const& Controller = Registry.get<ShipControllerComponent>(Entity);

			switch (Camera.Mode)
			{
				case CameraComponent::CameraMode::CAMERA_MODE_PERSPECTIVE: m_Projection = glm::perspective(glm::radians(Camera.Perspective.FieldOfView), AspectRatio, Camera.NearPlane, Camera.FarPlane); break;
				case CameraComponent::CameraMode::CAMERA_MODE_ORTHOGRAPHIC: m_Projection = glm::ortho(Camera.Orthographic.Left, Camera.Orthographic.Right, Camera.Orthographic.Bottom, Camera.Orthographic.Top, Camera.NearPlane, Camera.FarPlane); break;
			}

			switch (Controller.Mode)
			{
				case ShipControllerComponent::ControllerMode::CONTROLLER_MODE_FIRST_PERSON: m_View = glm::lookAt(Transform.WorldPosition, Transform.WorldPosition - Transform.LocalForward, Transform.LocalUp); break;
				case ShipControllerComponent::ControllerMode::CONTROLLER_MODE_ORBITAL: m_View = glm::lookAt(Transform.WorldPosition + Transform.LocalForward * Controller.Orbital.Distance, Transform.WorldPosition, Transform.LocalUp); break;
			}

			ClearDefaultFrameBuffer();

			DeferredGeometryPass(Registry);
			DeferredLightingPass(Registry, TransformSystem::GetWorldPosition(Transform));

			CopyDeferredGeometryDepthIntoDefaultFrameBuffer(TextureFilter::TEXTURE_FILTER_NEAREST);
			CopyDeferredLightingColorIntoDefaultFrameBuffer(TextureFilter::TEXTURE_FILTER_NEAREST);

			SkyBoxPass();
			PostProcessPass();

			//Gizmo::BeginLines(m_Projection, m_View, m_Model);
			//Gizmo::EndLines();
			//
			//Gizmo::BeginQuads(m_Projection, m_View, m_Model);
			//Gizmo::EndQuads();
			//
			//Gizmo::BeginLineBatch(m_Projection, m_View);
			//Gizmo::PushBatchLine(R32V3{ 0.0F, 0.0F, 0.0F }, R32V3{ 10.0F, 0.0F, 0.0F }, 0xFF0000FF);
			//Gizmo::PushBatchLine(R32V3{ 0.0F, 0.0F, 0.0F }, R32V3{ 0.0F, 10.0F, 0.0F }, 0x00FF00FF);
			//Gizmo::PushBatchLine(R32V3{ 0.0F, 0.0F, 0.0F }, R32V3{ 0.0F, 0.0F, 10.0F }, 0x0000FFFF);
			//Gizmo::PushBatchLineGrid(R32V3{ 0.0F, 0.0F, 0.0F }, 32, 1.0F, 0x484848FF);
			//Gizmo::DrawLineBatch();
			//Gizmo::EndLineBatch();
			//
			//Gizmo::BeginQuadBatch(m_Projection, m_View);
			//Gizmo::DrawQuadBatch();
			//Gizmo::EndQuadBatch();
		}
	}

	static VOID ClearDefaultFrameBuffer()
	{
		m_DefaultFrameBuffer->BindWrite();

		glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_DefaultFrameBuffer->UnbindWrite();
	}

	static VOID DeferredGeometryPass(entt::registry const& Registry)
	{
		m_DeferredGeometryFrameBuffer->BindWrite();

		glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		auto const View = Registry.view<TransformComponent, RenderComponent>();

		for (auto const Entity : View)
		{
			auto const& Transform = Registry.get<TransformComponent>(Entity);
			auto const& Renderable = Registry.get<RenderComponent>(Entity);

			m_Model = glm::identity<R32M4>();
			m_Model = glm::translate(m_Model, TransformSystem::GetWorldPosition(Transform));
			m_Model *= glm::mat4_cast(TransformSystem::GetWorldRotation(Transform));
			m_Model = glm::scale(m_Model, TransformSystem::GetWorldScale(Transform));

			Shader const* Shader = m_DeferredGeometryShaderReference->GetShader();

			if (Shader)
			{
				Shader->Bind();

				Shader->SetR32M4("Projection", m_Projection);
				Shader->SetR32M4("View", m_View);
				Shader->SetR32M4("Model", m_Model);

				Mesh* Mesh = Renderable.Mesh;

				MaterialReference const* MaterialReference = Mesh->GetMaterialReference();

				PrincipledBRDFMaterial const* Material = (PrincipledBRDFMaterial const*)MaterialReference->GetMaterial();

				if (Material)
				{
					Texture2DReference const* AlbedoTextureReference = Material->GetAlbedoTextureReference();
					Texture2DReference const* NormalTextureReference = Material->GetNormalTextureReference();
					Texture2DReference const* MetallicTextureReference = Material->GetMetallicTextureReference();
					Texture2DReference const* RoughnessTextureReference = Material->GetRoughnessTextureReference();
					Texture2DReference const* AmbientOcclusionTextureReference = Material->GetAmbientOcclusionTextureReference();
					Texture2DReference const* HeightTextureReference = Material->GetHeightTextureReference();
					Texture2DReference const* EmissiveTextureReference = Material->GetEmissiveTextureReference();
					Texture2DReference const* OpacityTextureReference = Material->GetOpacityTextureReference();

					if (AlbedoTextureReference->GetTexture2D()) AlbedoTextureReference->GetTexture2D()->Mount(0);
					if (NormalTextureReference->GetTexture2D()) NormalTextureReference->GetTexture2D()->Mount(1);
					if (MetallicTextureReference->GetTexture2D()) MetallicTextureReference->GetTexture2D()->Mount(2);
					if (RoughnessTextureReference->GetTexture2D()) RoughnessTextureReference->GetTexture2D()->Mount(3);
					if (AmbientOcclusionTextureReference->GetTexture2D()) AmbientOcclusionTextureReference->GetTexture2D()->Mount(4);
					if (HeightTextureReference->GetTexture2D()) HeightTextureReference->GetTexture2D()->Mount(5);
					if (EmissiveTextureReference->GetTexture2D()) EmissiveTextureReference->GetTexture2D()->Mount(6);
					if (OpacityTextureReference->GetTexture2D()) OpacityTextureReference->GetTexture2D()->Mount(7);

					VertexArray* VertexArray = Mesh->GetVertexArray();

					VertexArray->Bind();
					VertexArray->Draw(RenderMode::RENDER_MODE_TRIANGLES);
					VertexArray->Unbind();

					if (AlbedoTextureReference->GetTexture2D()) AlbedoTextureReference->GetTexture2D()->Unmount(0);
					if (NormalTextureReference->GetTexture2D()) NormalTextureReference->GetTexture2D()->Unmount(1);
					if (MetallicTextureReference->GetTexture2D()) MetallicTextureReference->GetTexture2D()->Unmount(2);
					if (RoughnessTextureReference->GetTexture2D()) RoughnessTextureReference->GetTexture2D()->Unmount(3);
					if (AmbientOcclusionTextureReference->GetTexture2D()) AmbientOcclusionTextureReference->GetTexture2D()->Unmount(4);
					if (HeightTextureReference->GetTexture2D()) HeightTextureReference->GetTexture2D()->Unmount(5);
					if (EmissiveTextureReference->GetTexture2D()) EmissiveTextureReference->GetTexture2D()->Unmount(6);
					if (OpacityTextureReference->GetTexture2D()) OpacityTextureReference->GetTexture2D()->Unmount(7);
				}

				Shader->Unbind();
			}
		}

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		m_DeferredGeometryFrameBuffer->UnbindWrite();
	}

	static VOID DeferredLightingPass(entt::registry const& Registry, R32V3 const& CameraPosition)
	{
		m_DeferredLightingFrameBuffer->BindWrite();

		glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		m_PointLightBuffer->Bind();
		m_PointLightBuffer->BeginBarrier();

		auto const View = Registry.view<TransformComponent, PointLightComponent>();

		U64 PointLightCount = 0;

		for (auto const Entity : View)
		{
			auto const& Transform = Registry.get<TransformComponent>(Entity);
			auto const& Light = Registry.get<PointLightComponent>(Entity);

			PointLight PointLight =
			{
				.Position = TransformSystem::GetWorldPosition(Transform),
				.Intensity = Light.Intensity,
				.Color = Light.Color,
				.Radius = Light.Radius,
			};

			m_PointLightBuffer->SetBuffer(&PointLight, PointLightCount, 1);

			PointLightCount++;

			if (PointLightCount > NUM_OF_POINT_LIGHTS)
			{
				break;
			}
		}

		m_PointLightBuffer->EndBarrier();
		m_PointLightBuffer->Unbind();

		Shader const* Shader = m_DeferredLightingShaderReference->GetShader();

		if (Shader)
		{
			Shader->Bind();

			Shader->SetU32("PointLightCount", (U32)PointLightCount);
			Shader->SetR32V3("CameraPosition", CameraPosition);

			m_PointLightBuffer->Mount(0);

			m_DeferredGeometryFrameBuffer->GetWorldPositionTexture()->Mount(0);
			m_DeferredGeometryFrameBuffer->GetWorldNormalTexture()->Mount(1);
			m_DeferredGeometryFrameBuffer->GetAlbedoTexture()->Mount(2);
			m_DeferredGeometryFrameBuffer->GetNormalTexture()->Mount(3);
			m_DeferredGeometryFrameBuffer->GetTangentTexture()->Mount(4);
			m_DeferredGeometryFrameBuffer->GetBitangentTexture()->Mount(5);
			m_DeferredGeometryFrameBuffer->GetMRAOTexture()->Mount(6);

			VertexArray* VertexArray = PrimitiveVertexArrays::GetPrincipledBRDFLightingQuad();

			VertexArray->Bind();
			VertexArray->Draw(RenderMode::RENDER_MODE_TRIANGLES);
			VertexArray->Unbind();

			m_DeferredGeometryFrameBuffer->GetWorldPositionTexture()->Unmount(0);
			m_DeferredGeometryFrameBuffer->GetWorldNormalTexture()->Unmount(1);
			m_DeferredGeometryFrameBuffer->GetAlbedoTexture()->Unmount(2);
			m_DeferredGeometryFrameBuffer->GetNormalTexture()->Unmount(3);
			m_DeferredGeometryFrameBuffer->GetTangentTexture()->Unmount(4);
			m_DeferredGeometryFrameBuffer->GetBitangentTexture()->Unmount(5);
			m_DeferredGeometryFrameBuffer->GetMRAOTexture()->Unmount(6);

			m_PointLightBuffer->Unmount(0);

			Shader->Unbind();
		}

		m_DeferredLightingFrameBuffer->UnbindWrite();
	}

	static VOID CopyDeferredGeometryDepthIntoDefaultFrameBuffer(TextureFilter const& Filter)
	{
		m_DeferredGeometryFrameBuffer->BindRead();
		m_DefaultFrameBuffer->BindWrite();

		glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_DEPTH_BUFFER_BIT, Filter);

		m_DefaultFrameBuffer->UnbindWrite();
		m_DeferredGeometryFrameBuffer->UnbindRead();
	}

	static VOID CopyDeferredLightingColorIntoDefaultFrameBuffer(TextureFilter const& Filter)
	{
		m_DeferredLightingFrameBuffer->BindRead();
		m_DefaultFrameBuffer->BindWrite();

		glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, Filter);

		m_DefaultFrameBuffer->UnbindWrite();
		m_DeferredLightingFrameBuffer->UnbindRead();
	}

	static VOID SkyBoxPass()
	{
		m_DefaultFrameBuffer->BindWrite();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glDepthFunc(GL_LEQUAL);

		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		Shader const* Shader = m_SpaceBoxShaderReference->GetShader();

		if (Shader)
		{
			Shader->Bind();

			Shader->SetR32M4("Projection", m_Projection);
			Shader->SetR32M4("View", R32M4{ R32M3{ m_View } });

			//AssetLoader::MaterialReference const& MaterialReference = AssetLoader::GetMaterialByName(""); // TODO
			//
			//SkyBoxMaterial* Material = (SkyBoxMaterial*)MaterialReference.Material;
			//
			//if (Material)
			//{
			//	AssetLoader::CubeMapReference const& CubeMapReference = AssetLoader::GetCubeMapByName(Material->Get);
			//
			//	CubeMap* CubeMap = Material->GetCubeMap();
			//
			//	if (CubeMap) CubeMap->Mount(0);
			//
			//	VertexArray* VertexArray = PrimitiveVertexArrays::GetSkyBoxCube();
			//
			//	VertexArray->Bind();
			//	VertexArray->Draw(RenderMode::RENDER_MODE_TRIANGLES);
			//	VertexArray->Unbind();
			//
			//	if (CubeMap) CubeMap->Unmount(0);
			//
			//	Shader->Bind();
			//}
		}

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		m_DefaultFrameBuffer->UnbindWrite();
	}

	static VOID PostProcessPass()
	{	
		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		
		Shader const* Shader = m_PassThroughShaderReference->GetShader();

		if (Shader)
		{		
			Shader->Bind();
		
			Shader->SetR32M4("Projection", m_Projection);
			Shader->SetR32M4("View", m_View);
		
			m_DefaultFrameBuffer->GetColorTexture()->Mount(0);
		
			VertexArray* VertexArray = PrimitiveVertexArrays::GetPostProcessQuad();

			VertexArray->Bind();
			VertexArray->Draw(RenderMode::RENDER_MODE_TRIANGLES);
			VertexArray->Unbind();
		
			m_DefaultFrameBuffer->GetColorTexture()->Unmount(0);
		
			Shader->Bind();
		}

		glDisable(GL_CULL_FACE);
	}
}