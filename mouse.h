#pragma once

#include <GLFW/glfw3.h>
#include "gameState.h"

extern float xpos;
extern float ypos;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	xpos = static_cast<float>(xposIn);
	ypos = static_cast<float>(yposIn);
	ypos = 1080.0f - ypos;
}

// Global variable to keep track of whether an action should be triggered
bool buttonIsPressed = false;
bool buttonIsReleased = false;
bool buttonIsInRangeNewGame = false;
bool buttonIsInRangeLoadGame = false;
bool buttonIsInRangeEditor = false;
bool buttonIsInRangeOptions = false;
bool buttonIsInRangeQuit = false;
bool buttonIsInRangeGridSizeX = false;
bool buttonIsInRangeGridSizeY = false;
bool buttonIsInRangeCellSizeArrow = false;
bool buttonIsInRangeGenerateButton = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeNewGame) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeLoadGame) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeEditor) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeOptions) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeQuit) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeGridSizeX) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeGridSizeY) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeCellSizeArrow) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRangeGenerateButton) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		buttonIsReleased = true;
		buttonIsPressed = false;
	}
}