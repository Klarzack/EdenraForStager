#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexOffset;
layout (location = 2) in vec2 vertexTexture0;
layout (location = 3) in vec2 vertexTexture1;
layout (location = 4) in vec2 vertexTexture2;
layout (location = 5) in vec2 vertexTexture3;

out vec2 texture;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main() {
	vec2 textureArray[] = {vertexTexture0, vertexTexture1, vertexTexture2, vertexTexture3};
	texture = textureArray[gl_VertexID];
	gl_Position = projection * view * transform * vec4(vertexPosition + vertexOffset, 1.0);
}