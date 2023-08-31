#version 330

in vec2 UV;
in vec3 position_worldspace;

in vec3 normal_cameraspace;
in vec3 eyeDirection_cameraspace;
in vec3 lightDirection_cameraspace;

in vec3 eyeDirection_tangentspace;
in vec3 lightDirection_tangentspace;

out vec3 color;

uniform sampler2D diffuseTextureSampler;
uniform sampler2D normalTextureSampler;
uniform sampler2D specularTextureSampler;
uniform vec3 lightPosition_worldspace;
uniform vec3 lightColor;
uniform float lightPower;

void main()
{

	vec3 materialDiffuseColor = texture(diffuseTextureSampler, UV).rgb;
	vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialDiffuseColor;
	vec3 materialSpecularColor = texture(specularTextureSampler, UV).rgb;

	vec3 textureNormal_tangentspace = normalize(
		texture(
			normalTextureSampler, vec2(UV.x, -UV.y)
		).rgb * 2 - 1
	);

	float distance = length(lightPosition_worldspace - position_worldspace);

	vec3 n = textureNormal_tangentspace;
	vec3 l = normalize( lightDirection_tangentspace );

	float cosTheta = clamp( dot(n, l), 0, 1 );

	vec3 E = normalize( eyeDirection_tangentspace );
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp( dot(E, R), 0, 1 );

	color = materialAmbientColor
    + materialDiffuseColor * lightColor * lightPower * cosTheta / (distance * distance)
	+ materialDiffuseColor * lightColor * lightPower * pow(cosAlpha, 100) / (distance * distance);

}