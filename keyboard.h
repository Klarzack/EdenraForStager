#pragma once

#include <GLFW/glfw3.h>

extern bool activateTextInput;
extern float xpos;
extern float ypos;

bool key1Pressed = false;
bool key1Released = false;
bool key2Pressed = false;
bool key2Released = false;
bool keyBackspacePressed = false;
bool keyBackspaceReleased = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS && activateTextInput) {
        key1Pressed = true;
        key1Released = false;
    }
    else if (key == GLFW_KEY_1 && action == GLFW_RELEASE && activateTextInput) {
        key1Released = true;
        key1Pressed = false;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && activateTextInput) {
        key2Pressed = true;
        key2Released = false;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_RELEASE && activateTextInput) {
        key2Pressed = false;
        key2Released = true;
    }
    else if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && activateTextInput) {
        keyBackspacePressed = true;
        keyBackspaceReleased = false;
    }
    else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE && activateTextInput) {
        keyBackspacePressed = false;
        keyBackspaceReleased = true;
    }
}