#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;

out vec2 UV;
out vec3 position_worldspace;

out vec3 normal_cameraspace;
out vec3 eyeDirection_cameraspace;
out vec3 lightDirection_cameraspace;

out vec3 eyeDirection_tangentspace;
out vec3 lightDirection_tangentspace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 lightPosition_worldspace;

void main()
{
	
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
	eyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	vec3 lightPosition_cameraspace = (V * vec4(lightPosition_worldspace, 1)).xyz;
	lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;

	normal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz;

	UV = vertexUV;

	vec3 vertexTangent_cameraspace = MV3x3 * vertexTangent_modelspace;
	vec3 vertexBitangent_cameraspace = MV3x3 * vertexBitangent_modelspace;
	vec3 vertexNormal_cameraspace = MV3x3 * vertexNormal_modelspace;

	mat3 TBN = transpose(
		mat3(
			vertexTangent_cameraspace, 
			vertexBitangent_cameraspace, 
			vertexNormal_cameraspace
		)
	);

	eyeDirection_tangentspace = TBN * eyeDirection_cameraspace;
	lightDirection_tangentspace = TBN * lightDirection_cameraspace;
}