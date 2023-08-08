#pragma once

#include "utilities.h"
#include "stb_image.h"

namespace {
	GLfloat ground[] = {
		 -9600.0f,  32.0f, 0.0f,  // top right
		9600.0f, 32.0f, 0.0f,  // bottom right
		 9600.0f, -32.0f, 0.0f,  // bottom left
		 -9600.0f,  -32.0f, 0.0f   // top left 
	};

	int groundIndices[] = {
		 0, 1, 2,  // first Triangle
		0, 2, 3   // second Triangle
	};

	GLfloat groundSquare[] = {
		-32.0f, 32.0f, 0.0f,
		32.0f, 32.0f, 0.0f,
		32.0f, -32.0f, 0.0f,
		-32.0f, -32.0f, 0.0f
	};

	int groundSquareIndices[] = {
		0, 1, 2,
		0, 2, 3
	};
}

struct Object {
	GLuint VAO{}, VBO{}, EBO{};
	float width;
	float height;
	glm::vec3 position{};

	void createObject(GLfloat* vertices, int verticesSize, int* indices, int indicesSize) {
		createVertexArrays(1, VAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, VBO, sizeof(float) * verticesSize, vertices, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, EBO, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

		unbindObjects(VAO);
		unbindObjects(VBO);
		unbindObjects(EBO);
	}

	void drawObject() {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void cleanUp() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
};

void activateTexture(GLuint shaderProgram, GLuint texture) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("C:/Users/istra/Edenra Engine/Edenra/Edenra/Images/UImenu/SpritesheetMenu.png", &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load Campaign.png" << std::endl;
	}
	stbi_image_free(data);

	//since we are using only 1 atlas, we can activate & bind texture & query the sampler location outside of the render loop
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture0"), 0);
}