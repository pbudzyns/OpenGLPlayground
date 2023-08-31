#version 330

layout(location = 0) in vec4 position_worldspace;

out vec2 position;

void main() {
	gl_Position = position_worldspace;
	position = position_worldspace.xy;
}