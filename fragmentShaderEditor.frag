#version 330 core
out vec4 FragColor;

in vec2 texture;

uniform sampler2D textureAtlasEditor;

void main() {
	FragColor = texture(textureAtlasEditor, texture);
}