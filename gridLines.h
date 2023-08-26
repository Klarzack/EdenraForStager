#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <vector>
#include "stb_image.h"
#include "glm/glm.hpp"

GLfloat gridLines[]{
	-32.0f, 32.0f, 0.0f,
	32.0f, 32.0f, 0.0f,
};

struct InstanceDataGridLines {
	glm::vec3 offset{};
};

std::vector<InstanceDataGridLines> gridLinesInstanceOffsets {
};

GLuint cellVAO{}, cellVBO{}, cellEBO{}, cellInstanceVBO{}, gridTexture{};

struct GridLines {
	void populateGrid(int columns, int rows) {
		InstanceDataGridLines instance;
		float x = 32.0f;
		for (int i{}; i < columns; i++) {
			instance.offset = glm::vec3(x, 0.0f, 0.0f);
			gridLinesInstanceOffsets.push_back(instance);
		}
	}
};