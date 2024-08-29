#version 460 core

//////////////////////////////////////////////////////////
// Macros
//////////////////////////////////////////////////////////

#define POINT_LIGHT_LINEAR 0.7
#define POINT_LIGHT_QUADRATIC 1.8

#define PI 3.14159265359
#define TAU 6.28318530718

//////////////////////////////////////////////////////////
// Types
//////////////////////////////////////////////////////////

struct PointLight
{
	vec3 Position;
	float Intensity;
	vec3 Color;
	float Radius;
};

//////////////////////////////////////////////////////////
// Storage Buffers
//////////////////////////////////////////////////////////

layout(binding = 0) buffer PointLightBuffer
{
    PointLight PointLights[];
};

//////////////////////////////////////////////////////////
// Samplers
//////////////////////////////////////////////////////////

layout(binding = 0) uniform sampler2D WorldPositionTextureSampler;
layout(binding = 1) uniform sampler2D WorldNormalTextureSampler;
layout(binding = 2) uniform sampler2D AlbedoTextureSampler;
layout(binding = 3) uniform sampler2D NormalTextureSampler;
layout(binding = 4) uniform sampler2D TangentTextureSampler;
layout(binding = 5) uniform sampler2D BitangentTextureSampler;
layout(binding = 6) uniform sampler2D MRAOTextureSampler;

//////////////////////////////////////////////////////////
// Inputs
//////////////////////////////////////////////////////////

layout(location = 0) in vec2 InputTextureCoords;

//////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////

layout(location = 0) out vec4 OutputColor;

//////////////////////////////////////////////////////////
// Uniforms
//////////////////////////////////////////////////////////

uniform uint PointLightCount;
uniform vec3 CameraPosition;

//////////////////////////////////////////////////////////
// BRDF
//////////////////////////////////////////////////////////

float DistributionGGX(vec3 N, vec3 H, float Roughness)
{
    float A = Roughness * Roughness;
    float A2 = A * A;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float Nom = A2;
    float Denom = (NdotH2 * (A2 - 1.0) + 1.0);

    Denom = PI * Denom * Denom;

    return Nom / Denom;
}

float GeometrySchlickGGX(float NdotV, float Roughness)
{
    float R = (Roughness + 1.0);
    float K = (R * R) / 8.0;

    float Nom = NdotV;
    float Denom = NdotV * (1.0 - K) + K;

    return Nom / Denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float Roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float GGX2 = GeometrySchlickGGX(NdotV, Roughness);
    float GGX1 = GeometrySchlickGGX(NdotL, Roughness);

    return GGX1 * GGX2;
}

vec3 FresnelSchlick(float CosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - CosTheta, 0.0, 1.0), 5.0);
}

//////////////////////////////////////////////////////////
// Entry Point
//////////////////////////////////////////////////////////

void main()
{
    vec3 FragmentWorldPosition = texture(WorldPositionTextureSampler, InputTextureCoords).rgb;
    vec3 FragmentWorldNormal = texture(WorldNormalTextureSampler, InputTextureCoords).rgb;
    vec3 FragmentAlbedo = texture(AlbedoTextureSampler, InputTextureCoords).rgb;
    vec3 FragmentNormal = texture(NormalTextureSampler, InputTextureCoords).rgb;
    vec3 FragmentTangent = texture(TangentTextureSampler, InputTextureCoords).rgb;
    vec3 FragmentBitangent = texture(BitangentTextureSampler, InputTextureCoords).rgb;
    vec3 FragmentMRAO = texture(MRAOTextureSampler, InputTextureCoords).rgb;

    float FragmentMetallic = FragmentMRAO.r;
    float FragmentRoughness = FragmentMRAO.g;
    float FragmentAmbientOcclusion = FragmentMRAO.b;

    vec3 ViewPosition = CameraPosition;
    vec3 WorldPosition = FragmentWorldPosition;

    vec3 N = FragmentNormal;
    vec3 V = normalize(ViewPosition - WorldPosition);

    // Calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
    vec3 F0 = vec3(0.04);

    F0 = mix(F0, FragmentAlbedo, FragmentMetallic);

    // Reflectance equation
    vec3 Lo = vec3(0.0);

    for (uint PointLightIndex = 0; PointLightIndex < PointLightCount; PointLightIndex++)
    {
        vec3 LightPosition = PointLights[PointLightIndex].Position;
        vec3 LightColor = PointLights[PointLightIndex].Color;
        float LightIntensity = PointLights[PointLightIndex].Intensity;
        float LightRadius = PointLights[PointLightIndex].Radius;

        // Calculate per-light radiance
        vec3 L = normalize(LightPosition - WorldPosition);
        vec3 H = normalize(V + L);

        float Distance = length(LightPosition - WorldPosition);
        float Attenuation = 1.0 / (1.0 + (POINT_LIGHT_LINEAR * Distance) + (POINT_LIGHT_QUADRATIC * Distance * Distance));

        Attenuation *= LightIntensity;

        vec3 Radiance = LightColor * Attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, FragmentRoughness);
        float G = GeometrySmith(N, V, L, FragmentRoughness);
        vec3 F = FresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

        vec3 Num = NDF * G * F; 
        float Denom = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // 0.0001 to prevent divide by zero
        vec3 Specular = Num / Denom;

        // KS is equal to Fresnel
        vec3 KS = F;

        // For energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (KD) should equal 1.0 - KS
        vec3 KD = vec3(1.0) - KS;

        // Multiply KD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals have no diffuse light)
        KD *= 1.0 - FragmentMetallic;

        // Scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);

        // Add to outgoing radiance Lo
        Lo += (KD * FragmentAlbedo / PI + Specular) * Radiance * NdotL; // Note that we already multiplied the BRDF by the Fresnel (KS) so we won't multiply by KS again
    }

    // Ambient lighting (note that the next IBL tutorial will replace this ambient lighting with environment lighting)
    vec3 Ambient = vec3(0.03) * FragmentAlbedo * FragmentAmbientOcclusion;

    vec3 Color = Ambient + Lo;

    // HDR tonemapping
    Color = Color / (Color + vec3(1.0));

    // Gamma correct
    Color = pow(Color, vec3(1.0 / 2.2));

    OutputColor = vec4(Color, 1.0);
}