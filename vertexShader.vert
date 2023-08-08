#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexture;

out vec2 texture;
uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main() {
	texture = vertexTexture;
	gl_Position = projection * view * transform * vec4(vertexPosition, 1.0);
}