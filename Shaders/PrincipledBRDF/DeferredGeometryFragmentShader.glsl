#version 460 core

//////////////////////////////////////////////////////////
// Samplers
//////////////////////////////////////////////////////////

layout(binding = 0) uniform sampler2D AlbedoTextureSampler;
layout(binding = 1) uniform sampler2D NormalTextureSampler;
layout(binding = 2) uniform sampler2D MetallicTextureSampler;
layout(binding = 3) uniform sampler2D RoughnessTextureSampler;
layout(binding = 4) uniform sampler2D AmbientOcclusionTextureSampler;
layout(binding = 5) uniform sampler2D HeightTextureSampler;
layout(binding = 6) uniform sampler2D EmissiveTextureSampler;
layout(binding = 7) uniform sampler2D OpacityTextureSampler;

//////////////////////////////////////////////////////////
// Inputs
//////////////////////////////////////////////////////////

layout(location = 0) in vec3 InputWorldPosition;
layout(location = 1) in vec3 InputWorldNormal;
layout(location = 2) in vec3 InputTangent;
layout(location = 3) in vec3 InputBitangent;
layout(location = 4) in vec2 InputTextureCoords;

//////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////

layout(location = 0) out vec3 OutputWorldPosition;
layout(location = 1) out vec3 OutputWorldNormal;
layout(location = 2) out vec3 OutputAlbedo;
layout(location = 3) out vec3 OutputNormal;
layout(location = 4) out vec3 OutputTangent;
layout(location = 5) out vec3 OutputBitangent;
layout(location = 6) out vec3 OutputMRAO;

//////////////////////////////////////////////////////////
// Entry Point
//////////////////////////////////////////////////////////

void main()
{
	vec4 Albedo = texture(AlbedoTextureSampler, InputTextureCoords);
	vec3 Normal = texture(NormalTextureSampler, InputTextureCoords).rgb;
	float Metallic = texture(MetallicTextureSampler, InputTextureCoords).r;
	float Roughness = texture(RoughnessTextureSampler, InputTextureCoords).r;
	float AmbientOcclusion = texture(AmbientOcclusionTextureSampler, InputTextureCoords).r;
	float Height = texture(HeightTextureSampler, InputTextureCoords).r;
	vec3 Emissive = texture(EmissiveTextureSampler, InputTextureCoords).rgb;
	float Opacity = texture(OpacityTextureSampler, InputTextureCoords).r;

	Normal = normalize((Normal * 2.0) - 1.0); // This normal is in tangent space

	mat3 TBN = mat3(InputTangent, InputBitangent, InputWorldNormal);

	Normal = normalize(TBN * Normal);

	OutputWorldPosition = InputWorldPosition;
	OutputWorldNormal = InputWorldNormal;
	OutputAlbedo = Albedo.rgb;
	OutputNormal = Normal;
	OutputTangent = InputTangent;
	OutputBitangent = InputBitangent;
	OutputMRAO = vec3(Metallic, Roughness, AmbientOcclusion);
}