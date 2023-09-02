#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utilities.h"
#include <glm/glm.hpp>
#include <vector>
#include "stb_image.h"
#include "mouse.h"

GLfloat menuQuad[]{
	-250.0f, 250.0f, 0.0f, 
	250.0f, 250.0f, 0.0f, 
	250.0f, -250.0f, 0.0f, 
	-250.0f, -250.0f, 0.0f
};

GLint menuQuadIndices[]{
	0, 1, 2,
	0, 2, 3
};

GLuint menuVAO{}, menuVBO{}, menuEBO{}, menuInstanceVBO{}, menuTexture{};

struct InstanceDataMenu {
	glm::vec3 offset{};
	glm::vec3 scale{};
	glm::vec2 textureCoords[4]{};
};

std::vector<InstanceDataMenu> menuInstances;

extern float xpos;
extern float ypos;

bool hoveringNewGame = false;
bool hoveringLoadGame = false;
bool hoveringEditor = false;
bool hoveringOptions = false;
bool hoveringQuit = false;
bool initialPressChecked = false;

struct Menu {

	void loadTexture() {
		glGenTextures(1, &menuTexture);
		glBindTexture(GL_TEXTURE_2D, menuTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load("C:/Users/istra/Edenra/Edenra/images/AtlasMenu.png", &width, &height, &nrChannels, STBI_rgb_alpha);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load textures for the menu" << std::endl;
		}
		stbi_image_free(data);
	}

	void populateMenu() {
		InstanceDataMenu instance;
		instance.offset = glm::vec3(960.0f, 540.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		//new game
		instance.textureCoords[0] = glm::vec2(0.09375f, 1.0f); // top left
		instance.textureCoords[1] = glm::vec2(0.2646484375f, 1.0f); // top right
		instance.textureCoords[2] = glm::vec2(0.2646484375f, 0.970703125f); // bottom right
		instance.textureCoords[3] = glm::vec2(0.09375f, 0.970703125f); // bottom left
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 440.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		//load game
		instance.textureCoords[0] = glm::vec2(0.09375f, 0.82421875f);
		instance.textureCoords[1] = glm::vec2(0.2646484375f, 0.82421875f);
		instance.textureCoords[2] = glm::vec2(0.2646484375f, 0.794921875f);
		instance.textureCoords[3] = glm::vec2(0.09375f, 0.794921875f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 340.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		//editor
		instance.textureCoords[0] = glm::vec2(0.2646484375f, 0.912109375f);
		instance.textureCoords[1] = glm::vec2(0.435546875f, 0.912109375f);
		instance.textureCoords[2] = glm::vec2(0.435546875f, 0.8828125f);
		instance.textureCoords[3] = glm::vec2(0.2646484375f, 0.8828125f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 240.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		//options
		instance.textureCoords[0] = glm::vec2(0.09375f, 0.912109375f);
		instance.textureCoords[1] = glm::vec2(0.2646484375f, 0.912109375f);
		instance.textureCoords[2] = glm::vec2(0.2646484375f, 0.8828125f);
		instance.textureCoords[3] = glm::vec2(0.09375f, 0.8828125f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 140.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		//quit
		instance.textureCoords[0] = glm::vec2(0.2646484375f, 1.0f);
		instance.textureCoords[1] = glm::vec2(0.435546875f, 1.0f);
		instance.textureCoords[2] = glm::vec2(0.435546875f, 0.970703125f);
		instance.textureCoords[3] = glm::vec2(0.2646484375f, 0.970703125f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(-1150.0f, -1540.0f, 0.0f);
		instance.scale = glm::vec3(0.1f, 0.1f, 0.0f);
		//background left
		instance.textureCoords[0] = glm::vec2(0.04443359375f, 1.0f);
		instance.textureCoords[1] = glm::vec2(0.0888671875f, 1.0f);
		instance.textureCoords[2] = glm::vec2(0.0888671875f, 0.853515625f);
		instance.textureCoords[3] = glm::vec2(0.04443359375f, 0.853515625f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(760.0f, 2065.0f, 0.0f);
		instance.scale = glm::vec3(0.256f, 0.256f, 0.0f);
		//dragon left
		instance.textureCoords[0] = glm::vec2(0.0390625f, 0.853515625f);
		instance.textureCoords[1] = glm::vec2(0.076171875f, 0.853515625f);
		instance.textureCoords[2] = glm::vec2(0.076171875f, 0.8037109375f);
		instance.textureCoords[3] = glm::vec2(0.0390625f, 0.8037109375f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(1160.0f, 2065.0f, 0.0f);
		instance.scale = glm::vec3(0.256f, 0.256f, 0.0f);
		//dragon right
		instance.textureCoords[0] = glm::vec2(0.0f, 0.85302734375f);
		instance.textureCoords[1] = glm::vec2(0.03857421875f, 0.85302734375f);
		instance.textureCoords[2] = glm::vec2(0.03857421875f, 0.802734375f);
		instance.textureCoords[3] = glm::vec2(0.0f, 0.802734375f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(980.0f, 540.0f, 0.0f);
		instance.scale = glm::vec3(2.0f, 1.0f, 0.0f);
		//background right
		instance.textureCoords[0] = glm::vec2(0.439453125f, 1.0f);
		instance.textureCoords[1] = glm::vec2(0.99365234375f, 1.0f);
		instance.textureCoords[2] = glm::vec2(0.99365234375f, 0.736328125f);
		instance.textureCoords[3] = glm::vec2(0.439453125f, 0.736328125f);
		menuInstances.push_back(instance);
	}

	void interactiveMenu(GLFWwindow* window) {
		if (buttonIsPressed && !initialPressChecked) {
			if (hoveringEditor) {
				gameState = gameEditor;
			}
			else if (hoveringNewGame) {
				std::cout << "You clicked New Game";
			}
			else if (hoveringLoadGame) {
				std::cout << "You clicked Load Game";
			}
			else if (hoveringOptions) {
				std::cout << "You clicked Options";
			}
			else if (hoveringQuit) {
				glfwTerminate();
			}
			initialPressChecked = true;
		}
		if (buttonIsReleased) {
			initialPressChecked = false;
		}
		
		//NewGame
		if (xpos > menuInstances[0].offset.x - 175.0f && xpos < menuInstances[0].offset.x + 175.0f && ypos > menuInstances[0].offset.y - 30.0f
			&& ypos < menuInstances[0].offset.y + 30.0f) {
			hoveringNewGame = true;
			menuInstances[0].textureCoords[0] = glm::vec2(0.09375f, 0.94140625f);
			menuInstances[0].textureCoords[1] = glm::vec2(0.2646484375f, 0.94140625f);
			menuInstances[0].textureCoords[2] = glm::vec2(0.2646484375f, 0.912109375f);
			menuInstances[0].textureCoords[3] = glm::vec2(0.09375f, 0.912109375f);
			//==================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringNewGame = false;
			menuInstances[0].textureCoords[0] = glm::vec2(0.09375f, 1.0f); // top left
			menuInstances[0].textureCoords[1] = glm::vec2(0.2646484375f, 1.0f); // top right
			menuInstances[0].textureCoords[2] = glm::vec2(0.2646484375f, 0.970703125f); // bottom right
			menuInstances[0].textureCoords[3] = glm::vec2(0.09375f, 0.970703125f); // bottom left
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		//Load Game
		if (xpos > menuInstances[1].offset.x - 175.0f && xpos < menuInstances[1].offset.x + 175.0f && ypos > menuInstances[1].offset.y - 30.0f
			&& ypos < menuInstances[1].offset.y + 30.0f) {
			hoveringLoadGame = true;
			menuInstances[1].textureCoords[0] = glm::vec2(0.09375f, 0.794921875f);
			menuInstances[1].textureCoords[1] = glm::vec2(0.2646484375f, 0.794921875f);
			menuInstances[1].textureCoords[2] = glm::vec2(0.2646484375f, 0.765625f);
			menuInstances[1].textureCoords[3] = glm::vec2(0.09375f, 0.765625f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringLoadGame = false;
			menuInstances[1].textureCoords[0] = glm::vec2(0.09375f, 0.82421875f);
			menuInstances[1].textureCoords[1] = glm::vec2(0.2646484375f, 0.82421875f);
			menuInstances[1].textureCoords[2] = glm::vec2(0.2646484375f, 0.794921875f);
			menuInstances[1].textureCoords[3] = glm::vec2(0.09375f, 0.794921875f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		//Editor
		if (xpos > menuInstances[2].offset.x - 175.0f && xpos < menuInstances[2].offset.x + 175.0f && ypos > menuInstances[2].offset.y - 30.0f
			&& ypos < menuInstances[2].offset.y + 30.0f) {
			hoveringEditor = true;
			menuInstances[2].textureCoords[0] = glm::vec2(0.2646484375f, 0.853515625f);
			menuInstances[2].textureCoords[1] = glm::vec2(0.435546875f, 0.853515625f);
			menuInstances[2].textureCoords[2] = glm::vec2(0.435546875f, 0.82421875f);
			menuInstances[2].textureCoords[3] = glm::vec2(0.2646484375f, 0.82421875f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringEditor = false;
			menuInstances[2].textureCoords[0] = glm::vec2(0.2646484375f, 0.912109375f);
			menuInstances[2].textureCoords[1] = glm::vec2(0.435546875f, 0.912109375f);
			menuInstances[2].textureCoords[2] = glm::vec2(0.435546875f, 0.8828125f);
			menuInstances[2].textureCoords[3] = glm::vec2(0.2646484375f, 0.8828125f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		//Options
		if (xpos > menuInstances[3].offset.x - 175.0f && xpos < menuInstances[3].offset.x + 175.0f && ypos > menuInstances[3].offset.y - 30.0f
			&& ypos < menuInstances[3].offset.y + 30.0f) {
			hoveringOptions = true;
			menuInstances[3].textureCoords[0] = glm::vec2(0.09375f, 0.853515625f);
			menuInstances[3].textureCoords[1] = glm::vec2(0.2646484375f, 0.853515625f);
			menuInstances[3].textureCoords[2] = glm::vec2(0.2646484375f, 0.82421875f);
			menuInstances[3].textureCoords[3] = glm::vec2(0.09375f, 0.82421875f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringOptions = false;
			menuInstances[3].textureCoords[0] = glm::vec2(0.09375f, 0.912109375f);
			menuInstances[3].textureCoords[1] = glm::vec2(0.2646484375f, 0.912109375f);
			menuInstances[3].textureCoords[2] = glm::vec2(0.2646484375f, 0.8828125f);
			menuInstances[3].textureCoords[3] = glm::vec2(0.09375f, 0.8828125f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		//Quit
		if (xpos > menuInstances[4].offset.x - 175.0f && xpos < menuInstances[4].offset.x + 175.0f && ypos > menuInstances[4].offset.y - 30.0f
			&& ypos < menuInstances[4].offset.y + 30.0f) {
			hoveringQuit = true;
			menuInstances[4].textureCoords[0] = glm::vec2(0.2646484375f, 0.94140625f);
			menuInstances[4].textureCoords[1] = glm::vec2(0.435546875f, 0.94140625f);
			menuInstances[4].textureCoords[2] = glm::vec2(0.435546875f, 0.912109375f);
			menuInstances[4].textureCoords[3] = glm::vec2(0.2646484375f, 0.912109375f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringQuit = false;
			menuInstances[4].textureCoords[0] = glm::vec2(0.2646484375f, 1.0f);
			menuInstances[4].textureCoords[1] = glm::vec2(0.435546875f, 1.0f);
			menuInstances[4].textureCoords[2] = glm::vec2(0.435546875f, 0.970703125f);
			menuInstances[4].textureCoords[3] = glm::vec2(0.2646484375f, 0.970703125f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		//this prevents mouse from clicking outside or on any other buttons. Some weird stuff going on here, old code, lazy to refactor
		if (hoveringNewGame) {
			menuInstances[6].offset = glm::vec3(776.0f, 530.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0390625f, 0.853515625f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.076171875f, 0.853515625f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.076171875f, 0.8037109375f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0390625f, 0.8037109375f);
			menuInstances[7].offset = glm::vec3(1123.0f, 530.5f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.0f, 0.85302734375f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.03857421875f, 0.85302734375f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.03857421875f, 0.802734375f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.0f, 0.802734375f);
			//==================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		} else if (hoveringLoadGame) {
			menuInstances[6].offset = glm::vec3(776.0f, 430.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0390625f, 0.853515625f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.076171875f, 0.853515625f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.076171875f, 0.8037109375f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0390625f, 0.8037109375f);
			menuInstances[7].offset = glm::vec3(1123.0f, 430.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.0f, 0.85302734375f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.03857421875f, 0.85302734375f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.03857421875f, 0.802734375f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.0f, 0.802734375f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (hoveringEditor) {
			menuInstances[6].offset = glm::vec3(776.0f, 330.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0390625f, 0.853515625f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.076171875f, 0.853515625f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.076171875f, 0.8037109375f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0390625f, 0.8037109375f);
			menuInstances[7].offset = glm::vec3(1123.0f, 330.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.0f, 0.85302734375f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.03857421875f, 0.85302734375f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.03857421875f, 0.802734375f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.0f, 0.802734375f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (hoveringOptions) {
			menuInstances[6].offset = glm::vec3(776.0f, 230.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0390625f, 0.853515625f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.076171875f, 0.853515625f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.076171875f, 0.8037109375f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0390625f, 0.8037109375f);
			menuInstances[7].offset = glm::vec3(1123.0f, 230.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.0f, 0.85302734375f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.03857421875f, 0.85302734375f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.03857421875f, 0.802734375f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.0f, 0.802734375f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (hoveringQuit) {
			menuInstances[6].offset = glm::vec3(776.0f, 130.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0390625f, 0.853515625f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.076171875f, 0.853515625f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.076171875f, 0.8037109375f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0390625f, 0.8037109375f);
			menuInstances[7].offset = glm::vec3(1123.0f, 130.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.0f, 0.85302734375f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.03857421875f, 0.85302734375f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.03857421875f, 0.802734375f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.0f, 0.802734375f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (!hoveringLoadGame && !hoveringNewGame && !hoveringEditor && !hoveringOptions && !hoveringQuit) {
			//==============================================================================================
			menuInstances[6].offset = glm::vec3(776.0f, 2065.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0390625f, 0.853515625f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.076171875f, 0.853515625f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.076171875f, 0.8037109375f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0390625f, 0.8037109375f);
			menuInstances[7].offset = glm::vec3(1123.0f, 2065.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.0f, 0.85302734375f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.03857421875f, 0.85302734375f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.03857421875f, 0.802734375f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.0f, 0.802734375f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceDataMenu)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
	}

	void createMenu() {
		createVertexArrays(1, menuVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, menuVBO, sizeof(menuQuad), menuQuad, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, menuEBO, sizeof(menuQuadIndices), menuQuadIndices, GL_STATIC_DRAW);

		createBufferObjects(GL_ARRAY_BUFFER, 1, menuInstanceVBO, sizeof(InstanceDataMenu) * menuInstances.size(), menuInstances.data(), GL_STATIC_DRAW);
		interpretData(1, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceDataMenu), (void*)0, 1);
		glVertexAttribDivisor(1, 1);
		interpretData(2, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceDataMenu), (void*)(sizeof(glm::vec3)), 2);
		glVertexAttribDivisor(2, 1);
		interpretData(3, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataMenu), (void*)(2 * sizeof(glm::vec3)), 3);
		glVertexAttribDivisor(3, 1);
		interpretData(4, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataMenu), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)), 4);
		glVertexAttribDivisor(4, 1);
		interpretData(5, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataMenu), (void*)(2 * sizeof(glm::vec3) + 2 * sizeof(glm::vec2)), 5);
		glVertexAttribDivisor(5, 1);
		interpretData(6, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceDataMenu), (void*)(2 * sizeof(glm::vec3) + 3 * sizeof(glm::vec2)), 6);
		glVertexAttribDivisor(6, 1);

		unbindObjects(menuVAO);
		unbindObjects(menuVBO);
		unbindObjects(menuEBO);
		unbindObjects(menuInstanceVBO);
	}

	void drawMenu() {
		glBindVertexArray(menuVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, static_cast<GLsizei>(menuInstances.size()));
		glBindVertexArray(0);
	}

	void deleteMenu() {
		glDeleteVertexArrays(1, &menuVAO);
		glDeleteBuffers(1, &menuVBO);
		glDeleteBuffers(1, &menuEBO);
		glDeleteBuffers(1, &menuInstanceVBO);
		glDeleteTextures(1, &menuTexture);
	}

	void activateAtlas(GLuint shaderProgram) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, menuTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureAtlasMenu"), 0);
	}
};