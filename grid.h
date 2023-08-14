#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <vector>
#include "stb_image.h"

GLfloat gridCell[] {
	-16.0f, 16.0f, 0.0f,
	16.0f, 16.0f, 0.0f,
	16.0f, -16.0f, 0.0f,
	-16.0f, -16.0f, 0.0f
};

int gridCellIndices[] {
	0, 1, 2,
	0, 2, 3
};

std::vector<glm::vec3> gridCellInstanceOffsets {
};

GLuint cellVAO{}, cellVBO{}, cellEBO{}, cellInstanceVBO{};

struct Grid {

	void populateGrid(int columns, int rows) {
		glm::vec3 position{};
		float vertexX = 16.0f;
		float vertexY = 16.0f;
		position = glm::vec3(vertexX, vertexY, 0.0f);
		gridCellInstanceOffsets.push_back(position);
		for (int i{1}; i <= columns; i++) {
			vertexX = 16.0f;
			if(i > 1)
				vertexY = vertexY + 35.0f;
			for (int j{ 1 }; j <= rows; j++) {
				if (j < 2)
					vertexX = 16.0f;
					position = glm::vec3(vertexX, vertexY, 0.0f);
					gridCellInstanceOffsets.push_back(position);
				vertexX = vertexX + 35.0f;
				position = glm::vec3(vertexX, vertexY, 0.0f);
				gridCellInstanceOffsets.push_back(position);
			}
		}
	}

	void createGrid() {
		createVertexArrays(1, cellVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, cellVBO, sizeof(gridCell), gridCell, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, cellEBO, sizeof(gridCellIndices), gridCellIndices, GL_STATIC_DRAW);

		createBufferObjects(GL_ARRAY_BUFFER, 1, cellInstanceVBO, sizeof(glm::vec3) * gridCellInstanceOffsets.size(), gridCellInstanceOffsets.data(), GL_STATIC_DRAW);
		interpretData(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 1);
		glVertexAttribDivisor(1, 1);

		unbindObjects(cellVAO);
		unbindObjects(cellVBO);
		unbindObjects(cellEBO);
		unbindObjects(cellInstanceVBO);
	}

	void drawGrid() {
		glBindVertexArray(cellVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, static_cast<GLsizei>(gridCellInstanceOffsets.size()));
		glBindVertexArray(0);
	}

	void deleteGrid() {
		glDeleteVertexArrays(1, &cellVAO);
		glDeleteBuffers(1, &cellVBO);
		glDeleteBuffers(1, &cellEBO);
		glDeleteBuffers(1, &cellInstanceVBO);
	}
};