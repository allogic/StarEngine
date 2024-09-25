#pragma once

struct GLFWwindow;

struct aiNode;
struct aiScene;
struct aiMaterial;

enum aiTextureType;

namespace Assimp
{
	class Importer;
}

namespace StarEngine
{
	class AssetReference;
	class MaterialReference;
	class ModelReference;
	class ShaderReference;
	class SkyBoxReference;
	class Texture2DReference;

	class IndexBuffer;
	class StorageBuffer;
	class UniformBuffer;
	class VertexBuffer;

	class DeferredGraphicsFrameBuffer;

	class Shader;

	class CubeMap;
	class Texture2D;

	class VertexArray;

	class Material;
	class Mesh;
	class Model;
	class SkyBox;

	class FileObserver;
	class WatchDog;
}