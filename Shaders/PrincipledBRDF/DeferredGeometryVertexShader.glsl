#version 460 core

//////////////////////////////////////////////////////////
// Inputs
//////////////////////////////////////////////////////////

layout (location = 0) in vec3 InputPosition;
layout (location = 1) in vec3 InputNormal;
layout (location = 2) in vec3 InputTangent;
layout (location = 3) in vec3 InputBitangent;
layout (location = 4) in vec2 InputTextureCoords;
layout (location = 5) in uint InputColor;

//////////////////////////////////////////////////////////
// Outputs
//////////////////////////////////////////////////////////

layout(location = 0) out vec3 OutputWorldPosition;
layout(location = 1) out vec3 OutputWorldNormal;
layout(location = 2) out vec3 OutputTangent;
layout(location = 3) out vec3 OutputBitangent;
layout(location = 4) out vec2 OutputTextureCoords;

//////////////////////////////////////////////////////////
// Uniforms
//////////////////////////////////////////////////////////

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

//////////////////////////////////////////////////////////
// Entry Point
//////////////////////////////////////////////////////////

void main()
{
	mat3 NormalMatrix = transpose(inverse(mat3(Model)));

	vec4 WorldPosition = Model * vec4(InputPosition, 1.0);

	OutputWorldPosition = WorldPosition.xyz;
	OutputWorldNormal = normalize(NormalMatrix * InputNormal);
	OutputTangent = InputTangent;
	OutputBitangent = InputBitangent;
	OutputTextureCoords = InputTextureCoords;

	gl_Position = Projection * View * WorldPosition;
}