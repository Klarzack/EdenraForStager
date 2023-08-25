#pragma once

#include <GLFW/glfw3.h>

extern bool activateTextInputGridX;
extern bool activateTextInputGridY;
extern float xpos;
extern float ypos;

bool key1Pressed = false;
bool key1Released = false;
bool key2Pressed = false;
bool key2Released = false;
bool key3Pressed = false;
bool key3Released = false;
bool key4Pressed = false;
bool key4Released = false;
bool key5Pressed = false;
bool key5Released = false;
bool key6Pressed = false;
bool key6Released = false;
bool key7Pressed = false;
bool key7Released = false;
bool key8Pressed = false;
bool key8Released = false;
bool key9Pressed = false;
bool key9Released = false;
bool key0Pressed = false;
bool key0Released = false;
bool keyBackspacePressed = false;
bool keyBackspaceReleased = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS && activateTextInputGridX) {
        key1Pressed = true;
        key1Released = false;
    }
    else if (key == GLFW_KEY_1 && action == GLFW_RELEASE && activateTextInputGridX) {
        key1Released = true;
        key1Pressed = false;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS && activateTextInputGridY) {
        key1Pressed = true;
        key1Released = false;
    }
    else if (key == GLFW_KEY_1 && action == GLFW_RELEASE && activateTextInputGridY) {
        key1Released = true;
        key1Pressed = false;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && activateTextInputGridX) {
        key2Pressed = true;
        key2Released = false;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_RELEASE && activateTextInputGridX) {
        key2Pressed = false;
        key2Released = true;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && activateTextInputGridY) {
        key2Pressed = true;
        key2Released = false;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_RELEASE && activateTextInputGridY) {
        key2Pressed = false;
        key2Released = true;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && activateTextInputGridX) {
        key3Pressed = true;
        key3Released = false;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_RELEASE && activateTextInputGridX) {
        key3Pressed = false;
        key3Released = true;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && activateTextInputGridY) {
        key3Pressed = true;
        key3Released = false;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_RELEASE && activateTextInputGridY) {
        key3Pressed = false;
        key3Released = true;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && activateTextInputGridX) {
        key4Pressed = true;
        key4Released = false;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_RELEASE && activateTextInputGridX) {
        key4Pressed = false;
        key4Released = true;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS && activateTextInputGridY) {
        key4Pressed = true;
        key4Released = false;
    }
    else if (key == GLFW_KEY_4 && action == GLFW_RELEASE && activateTextInputGridY) {
        key4Pressed = false;
        key4Released = true;
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS && activateTextInputGridX) {
        key5Pressed = true;
        key5Released = false;
    }
    else if (key == GLFW_KEY_5 && action == GLFW_RELEASE && activateTextInputGridX) {
        key5Pressed = false;
        key5Released = true;
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS && activateTextInputGridY) {
        key5Pressed = true;
        key5Released = false;
    }
    else if (key == GLFW_KEY_5 && action == GLFW_RELEASE && activateTextInputGridY) {
        key5Pressed = false;
        key5Released = true;
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS && activateTextInputGridX) {
        key6Pressed = true;
        key6Released = false;
    }
    else if (key == GLFW_KEY_6 && action == GLFW_RELEASE && activateTextInputGridX) {
        key6Pressed = false;
        key6Released = true;
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS && activateTextInputGridY) {
        key6Pressed = true;
        key6Released = false;
    }
    else if (key == GLFW_KEY_6 && action == GLFW_RELEASE && activateTextInputGridY) {
        key6Pressed = false;
        key6Released = true;
    }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS && activateTextInputGridX) {
        key7Pressed = true;
        key7Released = false;
    }
    else if (key == GLFW_KEY_7 && action == GLFW_RELEASE && activateTextInputGridX) {
        key7Pressed = false;
        key7Released = true;
    }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS && activateTextInputGridY) {
        key7Pressed = true;
        key7Released = false;
    }
    else if (key == GLFW_KEY_7 && action == GLFW_RELEASE && activateTextInputGridY) {
        key7Pressed = false;
        key7Released = true;
    }
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS && activateTextInputGridX) {
        key8Pressed = true;
        key8Released = false;
    }
    else if (key == GLFW_KEY_8 && action == GLFW_RELEASE && activateTextInputGridX) {
        key8Pressed = false;
        key8Released = true;
    }
     else if (key == GLFW_KEY_8 && action == GLFW_PRESS && activateTextInputGridY) {
        key8Pressed = true;
        key8Released = false;
    }
    else if (key == GLFW_KEY_8 && action == GLFW_RELEASE && activateTextInputGridY) {
        key8Pressed = false;
        key8Released = true;
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && activateTextInputGridX) {
        key9Pressed = true;
        key9Released = false;
    }
    else if (key == GLFW_KEY_9 && action == GLFW_RELEASE && activateTextInputGridX) {
        key9Pressed = false;
        key9Released = true;
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS && activateTextInputGridY) {
        key9Pressed = true;
        key9Released = false;
    }
    else if (key == GLFW_KEY_9 && action == GLFW_RELEASE && activateTextInputGridY) {
        key9Pressed = false;
        key9Released = true;
    }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && activateTextInputGridX) {
        key0Pressed = true;
        key0Released = false;
    }
    else if (key == GLFW_KEY_0 && action == GLFW_RELEASE && activateTextInputGridX) {
        key0Pressed = false;
        key0Released = true;
    }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS && activateTextInputGridY) {
        key0Pressed = true;
        key0Released = false;
    }
    else if (key == GLFW_KEY_0 && action == GLFW_RELEASE && activateTextInputGridY) {
        key0Pressed = false;
        key0Released = true;
    }
    else if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && activateTextInputGridX) {
        keyBackspacePressed = true;
        keyBackspaceReleased = false;
    }
    else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE && activateTextInputGridX) {
        keyBackspacePressed = false;
        keyBackspaceReleased = true;
    }
    else if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && activateTextInputGridY) {
        keyBackspacePressed = true;
        keyBackspaceReleased = false;
    }
    else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE && activateTextInputGridY) {
        keyBackspacePressed = false;
        keyBackspaceReleased = true;
    }
}