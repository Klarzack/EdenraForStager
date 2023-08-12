#pragma once

#include <GLFW/glfw3.h>

extern float xpos;
extern float ypos;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	xpos = static_cast<float>(xposIn);
	ypos = static_cast<float>(yposIn);
	ypos = 1080.0f - ypos;
}
