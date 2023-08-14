#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <glm/glm.hpp>
#include <vector>
#include "stb_image.h"

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

GLuint menuVAO{}, menuVBO{}, menuEBO{}, menuInstanceVBO{}, menuTexture;

struct InstanceData {
	glm::vec3 offset{};
	glm::vec3 scale{};
	glm::vec2 textureCoords[4];
};

std::vector<InstanceData> menuInstances;

extern float xpos;
extern float ypos;

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
			std::cout << "Failed to load AtlasMenu.png" << std::endl;
		}
		stbi_image_free(data);
	}

	void populateMenu() {
		InstanceData instance;
		instance.offset = glm::vec3(960.0f, 540.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.5333333333333333f, 0.2462311557788945f); // top left
		instance.textureCoords[1] = glm::vec2(0.715625f, 0.2462311557788945f); // top right
		instance.textureCoords[2] = glm::vec2(0.715625f, 0.2085427135678392f); // bottom right
		instance.textureCoords[3] = glm::vec2(0.5333333333333333f, 0.2085427135678392f); // bottom left
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 440.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.5333333333333333f, 0.2839195979899497f); 
		instance.textureCoords[1] = glm::vec2(0.715625f, 0.2839195979899497f); 
		instance.textureCoords[2] = glm::vec2(0.715625f, 0.2462311557788945f); 
		instance.textureCoords[3] = glm::vec2(0.5333333333333333f, 0.2462311557788945f); 
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 340.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
		instance.textureCoords[1] = glm::vec2(0.715625f, 0.321608040201005f);
		instance.textureCoords[2] = glm::vec2(0.715625f, 0.2839195979899497f);
		instance.textureCoords[3] = glm::vec2(0.5333333333333333f, 0.2839195979899497f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 240.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.5333333333333333f, 0.2085427135678392f);
		instance.textureCoords[1] = glm::vec2(0.715625f, 0.2085427135678392f);
		instance.textureCoords[2] = glm::vec2(0.715625f, 0.1708542713567839f);
		instance.textureCoords[3] = glm::vec2(0.5333333333333333f, 0.1708542713567839f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 140.0f, 0.0f);
		instance.scale = glm::vec3(0.7f, 0.12f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.5333333333333333f, 0.1708542713567839f);
		instance.textureCoords[1] = glm::vec2(0.715625f, 0.1708542713567839f);
		instance.textureCoords[2] = glm::vec2(0.715625f, 0.1331658291457286f);
		instance.textureCoords[3] = glm::vec2(0.5333333333333333f, 0.1331658291457286f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(960.0f, 540.0f, 0.0f);
		instance.scale = glm::vec3(3.84f, 2.16f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.0f, 1.0f);
		instance.textureCoords[1] = glm::vec2(1.0f, 1.0f);
		instance.textureCoords[2] = glm::vec2(1.0f, 0.321608040201005f);
		instance.textureCoords[3] = glm::vec2(0.0f, 0.321608040201005f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(760.0f, 2065.0f, 0.0f);
		instance.scale = glm::vec3(0.256f, 0.256f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.0f, 0.321608040201005f);
		instance.textureCoords[1] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
		instance.textureCoords[2] = glm::vec2(0.2666666666666667f, 0.0f);
		instance.textureCoords[3] = glm::vec2(0.0f, 0.0f);
		menuInstances.push_back(instance);
		instance.offset = glm::vec3(1160.0f, 2065.0f, 0.0f);
		instance.scale = glm::vec3(0.256f, 0.256f, 0.0f);
		instance.textureCoords[0] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
		instance.textureCoords[1] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
		instance.textureCoords[2] = glm::vec2(0.5333333333333333f, 0.0f);
		instance.textureCoords[3] = glm::vec2(0.2666666666666667f, 0.0f);
		menuInstances.push_back(instance);
	}

	void interactiveMenu(GLFWwindow* window) {

		bool hoveringNewGame = false;
		bool hoveringLoadGame = false;
		bool hoveringEditor = false;
		bool hoveringOptions = false;
		bool hoveringQuit = false;

		if (xpos > menuInstances[0].offset.x - 175.0f && xpos < menuInstances[0].offset.x + 175.0f && ypos > menuInstances[0].offset.y - 30.0f
			&& ypos < menuInstances[0].offset.y + 30.0f) {
			hoveringNewGame = true;
			menuInstances[0].textureCoords[0] = glm::vec2(0.715625f, 0.2462311557788945f);
			menuInstances[0].textureCoords[1] = glm::vec2(0.8979166666666667f, 0.2462311557788945f);
			menuInstances[0].textureCoords[2] = glm::vec2(0.8979166666666667f, 0.2085427135678392f);
			menuInstances[0].textureCoords[3] = glm::vec2(0.715625f, 0.2085427135678392f);
			//==================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringNewGame = false;
			menuInstances[0].textureCoords[0] = glm::vec2(0.5333333333333333f, 0.2462311557788945f); // top left
			menuInstances[0].textureCoords[1] = glm::vec2(0.715625f, 0.2462311557788945f); // top right
			menuInstances[0].textureCoords[2] = glm::vec2(0.715625f, 0.2085427135678392f); // bottom right
			menuInstances[0].textureCoords[3] = glm::vec2(0.5333333333333333f, 0.2085427135678392f); // bottom left
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}

		if (xpos > menuInstances[1].offset.x - 175.0f && xpos < menuInstances[1].offset.x + 175.0f && ypos > menuInstances[1].offset.y - 30.0f
			&& ypos < menuInstances[1].offset.y + 30.0f) {
			hoveringLoadGame = true;
			menuInstances[1].textureCoords[0] = glm::vec2(0.715625f, 0.2839195979899497f);
			menuInstances[1].textureCoords[1] = glm::vec2(0.8979166666666667f, 0.2839195979899497f);
			menuInstances[1].textureCoords[2] = glm::vec2(0.8979166666666667f, 0.2462311557788945f);
			menuInstances[1].textureCoords[3] = glm::vec2(0.715625f, 0.2462311557788945f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringLoadGame = false;
			menuInstances[1].textureCoords[0] = glm::vec2(0.5333333333333333f, 0.2839195979899497f);
			menuInstances[1].textureCoords[1] = glm::vec2(0.715625f, 0.2839195979899497f);
			menuInstances[1].textureCoords[2] = glm::vec2(0.715625f, 0.2462311557788945f);
			menuInstances[1].textureCoords[3] = glm::vec2(0.5333333333333333f, 0.2462311557788945f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}

		if (xpos > menuInstances[2].offset.x - 175.0f && xpos < menuInstances[2].offset.x + 175.0f && ypos > menuInstances[2].offset.y - 30.0f
			&& ypos < menuInstances[2].offset.y + 30.0f) {
			hoveringEditor = true;
			menuInstances[2].textureCoords[0] = glm::vec2(0.715625f, 0.321608040201005f);
			menuInstances[2].textureCoords[1] = glm::vec2(0.8979166666666667f, 0.321608040201005f);
			menuInstances[2].textureCoords[2] = glm::vec2(0.8979166666666667f, 0.2839195979899497f);
			menuInstances[2].textureCoords[3] = glm::vec2(0.715625f, 0.2839195979899497f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				gameState = gameEditor;
			}
		}
		else {
			hoveringEditor = false;
			menuInstances[2].textureCoords[0] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
			menuInstances[2].textureCoords[1] = glm::vec2(0.715625f, 0.321608040201005f);
			menuInstances[2].textureCoords[2] = glm::vec2(0.715625f, 0.2839195979899497f);
			menuInstances[2].textureCoords[3] = glm::vec2(0.5333333333333333f, 0.2839195979899497f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}

		if (xpos > menuInstances[3].offset.x - 175.0f && xpos < menuInstances[3].offset.x + 175.0f && ypos > menuInstances[3].offset.y - 30.0f
			&& ypos < menuInstances[3].offset.y + 30.0f) {
			hoveringOptions = true;
			menuInstances[3].textureCoords[0] = glm::vec2(0.715625f, 0.2085427135678392f);
			menuInstances[3].textureCoords[1] = glm::vec2(0.8979166666666667f, 0.2085427135678392f);
			menuInstances[3].textureCoords[2] = glm::vec2(0.8979166666666667f, 0.1708542713567839f);
			menuInstances[3].textureCoords[3] = glm::vec2(0.715625f, 0.1708542713567839f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringOptions = false;
			menuInstances[3].textureCoords[0] = glm::vec2(0.5333333333333333f, 0.2085427135678392f);
			menuInstances[3].textureCoords[1] = glm::vec2(0.715625f, 0.2085427135678392f);
			menuInstances[3].textureCoords[2] = glm::vec2(0.715625f, 0.1708542713567839f);
			menuInstances[3].textureCoords[3] = glm::vec2(0.5333333333333333f, 0.1708542713567839f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}

		if (xpos > menuInstances[4].offset.x - 175.0f && xpos < menuInstances[4].offset.x + 175.0f && ypos > menuInstances[4].offset.y - 30.0f
			&& ypos < menuInstances[4].offset.y + 30.0f) {
			hoveringQuit = true;
			menuInstances[4].textureCoords[0] = glm::vec2(0.715625f, 0.1708542713567839f);
			menuInstances[4].textureCoords[1] = glm::vec2(0.8979166666666667f, 0.1708542713567839f);
			menuInstances[4].textureCoords[2] = glm::vec2(0.8979166666666667f, 0.1331658291457286f);
			menuInstances[4].textureCoords[3] = glm::vec2(0.715625f, 0.1331658291457286f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else {
			hoveringQuit = false;
			menuInstances[4].textureCoords[0] = glm::vec2(0.5333333333333333f, 0.1708542713567839f);
			menuInstances[4].textureCoords[1] = glm::vec2(0.715625f, 0.1708542713567839f);
			menuInstances[4].textureCoords[2] = glm::vec2(0.715625f, 0.1331658291457286f);
			menuInstances[4].textureCoords[3] = glm::vec2(0.5333333333333333f, 0.1331658291457286f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}















































		if (hoveringNewGame && !hoveringLoadGame && !hoveringEditor) {
			menuInstances[6].offset = glm::vec3(760.0f, 565.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0f, 0.321608040201005f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.2666666666666667f, 0.0f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0f, 0.0f);
			menuInstances[7].offset = glm::vec3(1160.0f, 565.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.5333333333333333f, 0.0f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.2666666666666667f, 0.0f);
			//==================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		} else if (hoveringLoadGame && !hoveringNewGame && !hoveringEditor) {
			menuInstances[6].offset = glm::vec3(760.0f, 465.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0f, 0.321608040201005f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.2666666666666667f, 0.0f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0f, 0.0f);
			menuInstances[7].offset = glm::vec3(1160.0f, 465.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.5333333333333333f, 0.0f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.2666666666666667f, 0.0f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (hoveringEditor && !hoveringLoadGame && !hoveringNewGame) {
			menuInstances[6].offset = glm::vec3(760.0f, 365.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0f, 0.321608040201005f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.2666666666666667f, 0.0f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0f, 0.0f);
			menuInstances[7].offset = glm::vec3(1160.0f, 365.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.5333333333333333f, 0.0f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.2666666666666667f, 0.0f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (hoveringOptions && !hoveringLoadGame && !hoveringNewGame && !hoveringEditor) {
			menuInstances[6].offset = glm::vec3(760.0f, 265.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0f, 0.321608040201005f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.2666666666666667f, 0.0f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0f, 0.0f);
			menuInstances[7].offset = glm::vec3(1160.0f, 265.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.5333333333333333f, 0.0f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.2666666666666667f, 0.0f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (hoveringQuit && !hoveringLoadGame && !hoveringNewGame && !hoveringEditor && !hoveringOptions) {
			menuInstances[6].offset = glm::vec3(760.0f, 165.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0f, 0.321608040201005f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.2666666666666667f, 0.0f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0f, 0.0f);
			menuInstances[7].offset = glm::vec3(1160.0f, 165.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.5333333333333333f, 0.0f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.2666666666666667f, 0.0f);
			//===================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData) * menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
		else if (!hoveringLoadGame && !hoveringNewGame && !hoveringEditor && !hoveringOptions && !hoveringQuit) {
			//==============================================================================================
			menuInstances[6].offset = glm::vec3(760.0f, 2065.0f, 0.0f);
			menuInstances[6].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[6].textureCoords[0] = glm::vec2(0.0f, 0.321608040201005f);
			menuInstances[6].textureCoords[1] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[6].textureCoords[2] = glm::vec2(0.2666666666666667f, 0.0f);
			menuInstances[6].textureCoords[3] = glm::vec2(0.0f, 0.0f);
			menuInstances[7].offset = glm::vec3(1160.0f, 2065.0f, 0.0f);
			menuInstances[7].scale = glm::vec3(0.256f, 0.256f, 0.0f);
			menuInstances[7].textureCoords[0] = glm::vec2(0.2666666666666667f, 0.321608040201005f);
			menuInstances[7].textureCoords[1] = glm::vec2(0.5333333333333333f, 0.321608040201005f);
			menuInstances[7].textureCoords[2] = glm::vec2(0.5333333333333333f, 0.0f);
			menuInstances[7].textureCoords[3] = glm::vec2(0.2666666666666667f, 0.0f);
			//==============================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, menuInstanceVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(InstanceData)* menuInstances.size(), menuInstances.data());
			glBindVertexArray(menuVAO);
		}
	}

	void createMenu() {
		createVertexArrays(1, menuVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, menuVBO, sizeof(menuQuad), menuQuad, GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0, 0);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, menuEBO, sizeof(menuQuadIndices), menuQuadIndices, GL_STATIC_DRAW);

		createBufferObjects(GL_ARRAY_BUFFER, 1, menuInstanceVBO, sizeof(InstanceData) * menuInstances.size(), menuInstances.data(), GL_STATIC_DRAW);
		interpretData(1, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)0, 1);
		glVertexAttribDivisor(1, 1);
		interpretData(2, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(glm::vec3)), 2);
		glVertexAttribDivisor(2, 1);
		interpretData(3, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(2 * sizeof(glm::vec3)), 3);
		glVertexAttribDivisor(3, 1);
		interpretData(4, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)), 4);
		glVertexAttribDivisor(4, 1);
		interpretData(5, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(2 * sizeof(glm::vec3) + 2 * sizeof(glm::vec2)), 5);
		glVertexAttribDivisor(5, 1);
		interpretData(6, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(2 * sizeof(glm::vec3) + 3 * sizeof(glm::vec2)), 6);
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
		//since we are using only 1 atlas for render the menu, we can activate & bind texture & query the sampler location outside of the render loop
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, menuTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureAtlas"), 0);
	}
};