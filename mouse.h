#pragma once

#include <GLFW/glfw3.h>
#include "gameState.h"
#include "stb_image.h"

extern float xpos;
extern float ypos;

GLuint cursorTexture{};

struct CustomCursor {
    void loadImage(GLFWwindow* window) {
        int width, height, nrChannels;
        unsigned char* data = stbi_load("C:/Users/istra/Edenra/Edenra/images/Cursor.png", &width, &height, &nrChannels, STBI_rgb_alpha);
        if (!data) {
            std::cout << "Failed to load texture for the cursor" << std::endl;
            return;
        }

        GLFWimage image;
        image.width = width;
        image.height = height;
        image.pixels = data;

        GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);

        // Set the cursor for a window (assuming you have a window pointer named 'window')
        glfwSetCursor(window, cursor);

        stbi_image_free(data);
    }
};

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	xpos = static_cast<float>(xposIn);
	ypos = static_cast<float>(yposIn);
	ypos = 1080.0f - ypos;
}

// Global variable to keep track of whether an action should be triggered
bool buttonIsPressed = false;
bool buttonIsReleased = false;
bool buttonIsInRangeGridSizeX = false;
bool buttonIsInRangeGridSizeY = false;
bool buttonIsInRangeCellSizeArrow = false;
bool buttonIsInRangeGenerateButton = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		buttonIsPressed = true;
		buttonIsReleased = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		buttonIsReleased = true;
		buttonIsPressed = false;
	}
}