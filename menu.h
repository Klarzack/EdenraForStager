#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

GLfloat box1[] = {
	-125.0f, 25.0f, 0.0f,
	125.0f, 25.0f, 0.0f,
	125.0f, -25.0f, 0.0f,
	-125.0f, -25.0f, 0.0f
};

int box1indices[] = {
	0, 1, 2,
	0, 2, 3
};

struct Menu {

	GLuint VAOmenu{}, VBOmenu{}, EBOmenu{};
	float width{};
	float height{};
	glm::vec3 position{};

	void createMenu() {

		createVertexArrays(1, VAOmenu);
		createBufferObjects(GL_ARRAY_BUFFER, 1, VBOmenu, sizeof(box1), box1, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, EBOmenu, sizeof(box1indices), box1indices, GL_STATIC_DRAW);

		unbindObjects(VAOmenu);
		unbindObjects(VBOmenu);
		unbindObjects(EBOmenu);
	}

	void renderMenu() {
		glBindVertexArray(VAOmenu);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void cleanUp() {
		glDeleteVertexArrays(1, &VAOmenu);
		glDeleteBuffers(1, &VBOmenu);
		glDeleteBuffers(1, &EBOmenu);
	}
};