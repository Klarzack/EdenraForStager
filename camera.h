#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "grid.h"

struct Camera {

	float width{ 1920 };
	float height{ 1080 };
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	void updateView() {
		view = glm::translate(glm::mat4(1.0f), -cameraPosition);
	}

	void createCamera() {
		projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
	}

	void useCamera(GLuint shaderProgram) {
		GLuint viewLocation = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		GLuint projectionLocation = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	}

	//move camera around
	void freeCamera(glm::vec3& screenCenter, double deltaTime, float xpos, float ypos) {
		if (xpos > screenCenter.x + 958.0f) {
			cameraPosition.x += 800.0f * (float)deltaTime;
		}
		else if (xpos < screenCenter.x - 958.0f) {
			cameraPosition.x -= 800.0f * (float)deltaTime;
		}

		if (ypos > screenCenter.y + 538.0f) {
			cameraPosition.y += 800.0f * (float)deltaTime;
		}
		else if (ypos < screenCenter.y - 538.0f) {
			cameraPosition.y -= 800.0f * (float)deltaTime;
		}
	}

	void activateFrustumCulling() {
	visibleCells.clear();
	// camera bounds with padding
	float leftBound = cameraPosition.x - 100; // + 100px padding on all sides
	float rightBound = cameraPosition.x + 2020;
	float topBound = cameraPosition.y + 1180;
	float bottomBound = cameraPosition.y - 100;

		for (auto& instance : gridCellInstanceOffsets) {

			if (instance.offset.x >= leftBound && instance.offset.x <= rightBound && instance.offset.y >= bottomBound
				&& instance.offset.y <= topBound) {
				visibleCells.push_back(instance);
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, cellInstanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceDataGrid) * visibleCells.size(), visibleCells.data(), GL_DYNAMIC_DRAW);
		glBindVertexArray(cellVAO);
	}
};
