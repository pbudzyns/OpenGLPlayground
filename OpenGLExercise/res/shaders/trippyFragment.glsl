#version 330

in vec2 position;

out vec3 color;

uniform float time;
uniform float xScale;
uniform float yScale;
uniform float zScale;

void main() {

	float r = abs(sin(position.x * xScale + time));
	float g = abs(cos(position.y * yScale + time));
	float b = abs(sin(position.y * zScale + time) + cos(position.x * zScale + time));
	color = vec3(r, g, b);
}