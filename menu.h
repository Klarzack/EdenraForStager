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

void rendeMenuElements(GLFWwindow* window, glm::mat4 menuBoxOne, glm::mat4 menuBoxTwo, glm::mat4 menuBoxThree, Menu& menuBox1, Menu& menuBox2, Menu& menuBox3, GLuint
	menuBox1Location, GLuint menuBox2Location, GLuint menuBox3Location) {
	menuBoxOne = glm::mat4(1.0f);
	menuBoxOne = glm::translate(menuBoxOne, menuBox1.position);
	if (menuBox1.position.x - menuBox1.width < xpos && menuBox1.position.x + menuBox1.width > xpos && menuBox1.position.y - menuBox1.height < ypos
		&& menuBox1.position.y + menuBox1.height > ypos) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			gameState = gameRunning;
		}
	}
	glUniformMatrix4fv(menuBox1Location, 1, GL_FALSE, glm::value_ptr(menuBoxOne));
	menuBox1.renderMenu();

	menuBoxTwo = glm::mat4(1.0f);
	menuBoxTwo = glm::translate(menuBoxTwo, menuBox2.position);
	if (menuBox2.position.x - menuBox2.width < xpos && menuBox2.position.x + menuBox2.width > xpos && menuBox2.position.y - menuBox2.height < ypos
		&& menuBox2.position.y + menuBox2.height > ypos) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			gameState = gameOptions;
		}
	}
	glUniformMatrix4fv(menuBox2Location, 1, GL_FALSE, glm::value_ptr(menuBoxTwo));
	menuBox2.renderMenu();

	menuBoxThree = glm::mat4(1.0f);
	menuBoxThree = glm::translate(menuBoxThree, menuBox3.position);
	if (menuBox3.position.x - menuBox3.width < xpos && menuBox3.position.x + menuBox3.width > xpos && menuBox3.position.y - menuBox3.height < ypos
		&& menuBox3.position.y + menuBox3.height > ypos) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			//more code in here to clean up resources please!!!
			glfwTerminate();
		}
	}
	glUniformMatrix4fv(menuBox3Location, 1, GL_FALSE, glm::value_ptr(menuBoxThree));
	menuBox3.renderMenu();
};