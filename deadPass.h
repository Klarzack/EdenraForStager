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
	GLuint VAO, VBO, EBO, texture;
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