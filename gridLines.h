#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <vector>
#include "stb_image.h"
#include "glm/glm.hpp"

GLfloat gridLines[]{
	// horizontal line
	-32.0f, 32.0f, 0.0f,
	32.0f, 32.0f, 0.0f,

	// vertical line
	0.0f, 0.0f, 0.0f,
	0.0f, 64.0f, 0.0f
};

struct InstanceDataGridLines {
	glm::vec3 offset{};
};

std::vector<InstanceDataGridLines> gridLinesInstanceOffsets {
};

GLuint linesVAO{}, linesVBO{}, linesInstanceVBO{};

struct GridLines {

	void populateGridLines(int columns, int rows) { //columns are number of squares UP, on the X axis; 2nd param is width in pixels for the grid line
		InstanceDataGridLines instance;
		float y = 64.0f;
		for (int i{}; i < columns; i++) {
			instance.offset = glm::vec3(0.0, y * i - 32.0f, 0.0f);
			gridLinesInstanceOffsets.push_back(instance);
			for (int j{}; j < rows; j++) {
				instance.offset = glm::vec3(64.0f * j, y * i - 32.0f, 0.0f);
				gridLinesInstanceOffsets.push_back(instance);
			}
		}
	}

	void createGridLines() {
		createVertexArrays(1, linesVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, linesVBO, sizeof(gridLines), gridLines, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);

		createBufferObjects(GL_ARRAY_BUFFER, 1, linesInstanceVBO, sizeof(InstanceDataGridLines) * gridLinesInstanceOffsets.size(), gridLinesInstanceOffsets.data(), GL_STATIC_DRAW);
		interpretData(1, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceDataGridLines), (void*)0, 1);
		glVertexAttribDivisor(1, 1);
	}

	void drawGridLines(GLuint shaderProgram) {
		glUseProgram(shaderProgram);
		glBindVertexArray(linesVAO);
		glDrawArraysInstanced(GL_LINES, 0, 4, static_cast<GLsizei>(gridLinesInstanceOffsets.size()));
		glBindVertexArray(0);
	}

	void deleteGridLines() {
		gridLinesInstanceOffsets.clear();
		glDeleteVertexArrays(1, &linesVAO);
		glDeleteBuffers(1, &linesVBO);
		glDeleteBuffers(1, &linesInstanceVBO);
	}
};