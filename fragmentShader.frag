#version 330 core

out vec4 FragColor;
in vec2 texture;	
uniform sampler2D texture0;

void main() {
	FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}