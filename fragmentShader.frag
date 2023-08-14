#version 330 core
out vec4 FragColor;

in vec2 texture;

uniform sampler2D textureAtlas;

void main() {
	FragColor = texture(textureAtlas, texture);
}