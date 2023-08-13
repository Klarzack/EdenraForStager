#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <glm/glm.hpp>
#include <vector>

GLfloat backgroundMenu[]{
	-960.0f, 540.0f, 0.0f,
	960.0f, 540.0f, 0.0f,
	960.0f, -540.0f, 0.0f,
	-960.0f, -540.0f, 0.0f
};

GLint backrgoundMenuIndices[]{
	0, 1, 2,
	0, 2, 3
};

std::vector<glm::vec3> menuInstanceOffsets {
	
};

GLuint menuVAO{}, menuVBO{}, menuEBO{}, menuInstanceVBO{};

struct Menu {

	void populateMenu() {
		glm::vec3 position{};
		position = glm::vec3(960.0f, 540.0f, 0.0f);
		menuInstanceOffsets.push_back(position);
	}

	void scaleMenu() {
		glm::vec3 scale{};
		scale = glm::vec3(350.0f, 100.0f, 0.0f);
	}

	void createMenu() {
		createVertexArrays(1, menuVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, menuVBO, sizeof(backgroundMenu), backgroundMenu, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, menuEBO, sizeof(backrgoundMenuIndices), backrgoundMenuIndices, GL_STATIC_DRAW);

		createBufferObjects(GL_ARRAY_BUFFER, 1, menuInstanceVBO, sizeof(glm::vec3) * menuInstanceOffsets.size(), menuInstanceOffsets.data(), GL_STATIC_DRAW);
		interpretData(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 1);
		glVertexAttribDivisor(1, 1);

		unbindObjects(menuVAO);
		unbindObjects(menuVBO);
		unbindObjects(menuEBO);
		unbindObjects(menuInstanceVBO);
	}

	void drawMenu() {
		glBindVertexArray(menuVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 12);
		glBindVertexArray(0);
	}

	void deleteMenu() {
		glDeleteVertexArrays(1, &menuVAO);
		glDeleteBuffers(1, &menuVBO);
		glDeleteBuffers(1, &menuEBO);
		glDeleteBuffers(1, &menuInstanceVBO);
	}

};