#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexOffset; 
layout (location = 2) in vec3 vertexScale; 
layout (location = 3) in vec2 vertexTextureCoords0; 
layout (location = 4) in vec2 vertexTextureCoords1; 
layout (location = 5) in vec2 vertexTextureCoords2; 
layout (location = 6) in vec2 vertexTextureCoords3;

out vec2 texture;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main() {
    vec2 instanceTextureCoords[] = {vertexTextureCoords0, vertexTextureCoords1, vertexTextureCoords2, vertexTextureCoords3};
    texture = instanceTextureCoords[gl_VertexID];
    gl_Position = projection * view * transform * vec4(vertexPosition * vertexScale + vertexOffset, 1.0);
}