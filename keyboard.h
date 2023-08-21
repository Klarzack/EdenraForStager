#pragma once

#include <GLFW/glfw3.h>

extern float xpos;
extern float ypos;

bool keyPressed = false;
bool keyReleased = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        keyPressed = true;
        keyReleased = false;
    }
    else if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
        keyPressed = false;
        keyReleased = true;
    }
}