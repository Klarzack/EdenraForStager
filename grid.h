#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <vector>
#include "stb_image.h"
#include "glm/glm.hpp"

GLfloat gridCell[]{
	-32.0f, 32.0f, 0.0f,
	32.0f, 32.0f, 0.0f,
	32.0f, -32.0f, 0.0f,
	-32.0f, -32.0f, 0.0f
};

int gridCellIndices[]{
	0, 1, 2,
	0, 2, 3
};

struct InstanceDataGrid {
	glm::vec3 offset{};
	glm::vec2 textureCoords[4]{};
};

std::vector<InstanceDataGrid> gridCellInstanceOffsets{}; //main vector where all the grid cells are stored

std::vector<InstanceDataGrid> visibleCells{}; //vector that contains the cells within the camera view - frustum culling vector

GLuint cellVAO{}, cellVBO{}, cellEBO{}, cellInstanceVBO{}, gridTexture{};

struct Grid {

	void loadTexture() {
		glGenTextures(1, &gridTexture);
		glBindTexture(GL_TEXTURE_2D, gridTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("C:/Users/istra/Edenra/Edenra/images/AtlasEditor.png", &width, &height, &nrChannels, STBI_rgb_alpha);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture for the grid" << std::endl;
		}
		stbi_image_free(data);
	}
	// this is my way of generating a grid. In case the grid below doesn't work as I want it to, come back to this worse, yet workable version

	//void populateGrid(int columns, int rows) {
	//	//FIRST PARAMETER IS Y, SECOND PARAMETER IS X, MEANING COLUMNS IS Y, ROWS IS X HERE
	//	InstanceDataGrid instance;
	//	float vertexX = 32.0f;
	//	float vertexY = 32.0f;
	//	instance.offset = glm::vec3(vertexX, vertexY, 0.0f);
	//	instance.textureCoords[0] = glm::vec2(1.0f, 0.970703125f); // top left
	//	instance.textureCoords[1] = glm::vec2(0.048828125f, 0.970703125f); // top right
	//	instance.textureCoords[2] = glm::vec2(0.048828125f, 0.962890625f); // bottom right
	//	instance.textureCoords[3] = glm::vec2(0.041015625f, 0.962890625f); // bottom left
	//	gridCellInstanceOffsets.push_back(instance);
	//	for (int i{ 1 }; i <= columns; i++) {
	//		vertexX = 32.0f;
	//		if (i > 1) {
	//			vertexY = vertexY + 64.0f;
	//		}
	//		for (int j{ 1 }; j <= rows; j++) {
	//			if (j < 2) {
	//				vertexX = 32.0f;
	//				instance.offset = glm::vec3(vertexX, vertexY, 0.0f);
	//				instance.textureCoords[0] = glm::vec2(0.041015625f, 0.970703125f); // top left
	//				instance.textureCoords[1] = glm::vec2(0.048828125f, 0.970703125f); // top right
	//				instance.textureCoords[2] = glm::vec2(0.048828125f, 0.962890625f); // bottom right
	//				instance.textureCoords[3] = glm::vec2(0.041015625f, 0.962890625f); // bottom left
	//				gridCellInstanceOffsets.push_back(instance);
	//			}
	//			vertexX = vertexX + 64.0f;
	//			instance.offset = glm::vec3(vertexX, vertexY, 0.0f);
	//			instance.textureCoords[0] = glm::vec2(0.041015625f, 0.970703125f); // top left  Y is inverted, so if it starts at height 60, it's 2048 - 60
	//			instance.textureCoords[1] = glm::vec2(0.048828125f, 0.970703125f); // top right same here
	//			instance.textureCoords[2] = glm::vec2(0.048828125f, 0.962890625f); // bottom right same here
	//			instance.textureCoords[3] = glm::vec2(0.041015625f, 0.962890625f); // bottom left same here
	//			gridCellInstanceOffsets.push_back(instance);
	//		}
	//	}
	//}

	void populateGrid(int columns, int rows) {
		float initialX = 32.0f;
		float initialY = 32.0f;
		float xOffset = 64.0f;  // Offset value for each cell
		float yOffset = 64.0f;  // Offset value for each cell

		for (int i = 0; i < columns; ++i) {
			for (int j = 0; j < rows; ++j) {
				InstanceDataGrid instance;
				float vertexX = initialX + j * xOffset;
				float vertexY = initialY + i * yOffset;

				instance.offset = glm::vec3(vertexX, vertexY, 0.0f);
				instance.textureCoords[0] = glm::vec2(0.041015625f, 0.970703125f); // top left
				instance.textureCoords[1] = glm::vec2(0.048828125f, 0.970703125f); // top right
				instance.textureCoords[2] = glm::vec2(0.048828125f, 0.962890625f); // bottom right
				instance.textureCoords[3] = glm::vec2(0.041015625f, 0.962890625f); // bottom left

				gridCellInstanceOffsets.push_back(instance);
			}
		}
	}

	void createGrid() {
		createVertexArrays(1, cellVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, cellVBO, sizeof(gridCell), gridCell, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, cellEBO, sizeof(gridCellIndices), gridCellIndices, GL_STATIC_DRAW);

		createBufferObjects(GL_ARRAY_BUFFER, 1, cellInstanceVBO, sizeof(InstanceDataGrid) * gridCellInstanceOffsets.size(), gridCellInstanceOffsets.data(), GL_STATIC_DRAW);
		interpretData(1, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceDataGrid), (void*)0, 1);
		glVertexAttribDivisor(1, 1);
		interpretData(2, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataGrid), (void*)(sizeof(glm::vec3)), 2);
		glVertexAttribDivisor(2, 1);
		interpretData(3, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataGrid), (void*)(sizeof(glm::vec3) + 1 * sizeof(glm::vec2)), 3);
		glVertexAttribDivisor(3, 1);
		interpretData(4, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataGrid), (void*)(sizeof(glm::vec3) + 2 * sizeof(glm::vec2)), 4);
		glVertexAttribDivisor(4, 1);
		interpretData(5, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataGrid), (void*)(sizeof(glm::vec3) + 3 * sizeof(glm::vec2)), 5);
		glVertexAttribDivisor(5, 1);

		unbindObjects(GL_VERTEX_ARRAY);
		unbindObjects(GL_ARRAY_BUFFER);
		unbindObjects(GL_ELEMENT_ARRAY_BUFFER);
	}

	void drawGrid() {
		glBindVertexArray(cellVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, static_cast<GLsizei>(visibleCells.size()));
		glBindVertexArray(0);
	}

	void deleteGrid() {
		gridCellInstanceOffsets.clear();
		glDeleteVertexArrays(1, &cellVAO);
		glDeleteBuffers(1, &cellVBO);
		glDeleteBuffers(1, &cellEBO);
		glDeleteBuffers(1, &cellInstanceVBO);
	}

	void activateAtlas(GLuint shaderProgram) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, gridTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureAtlasGrid"), 1);
	}
};