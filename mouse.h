#pragma once

#include <GLFW/glfw3.h>

extern float xpos;
extern float ypos;

/*
When u hover, it's brighter, when u click, it's another color, and when you release, it's back to its hover state
*/

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	xpos = static_cast<float>(xposIn);
	ypos = static_cast<float>(yposIn);
	ypos = 1080.0f - ypos;
}

// Global variable to keep track of whether an action should be triggered
bool buttonIsPressed = false;
bool buttonIsReleased = false;
bool buttonIsInRange = false;
bool mouseClicksEnabled = true;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRange && mouseClicksEnabled) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && buttonIsInRange && mouseClicksEnabled) {
		buttonIsReleased = true;
		buttonIsPressed = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !buttonIsInRange) {
		mouseClicksEnabled = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && buttonIsInRange) {
		mouseClicksEnabled = true;
	}
}