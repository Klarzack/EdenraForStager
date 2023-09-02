#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <glm/glm.hpp>
#include <vector>
#include "stb_image.h"
#include "mouse.h"
#include "keyboard.h"
#include "gameState.h"

struct EditorVertices {
	glm::vec3 position[4];
	glm::vec2 texture[4];
};

struct EditorIndices {
	int indices[6];
};

GLuint editorVAO{}, editorVBO{}, editorEBO{}, editorTexture{};

std::vector<EditorVertices>verticesEditor{};
std::vector<EditorIndices>indicesEditor{};
std::vector<GLfloat>flattenedVertices{};
std::vector<GLint>flattenedIndices{};

extern float xpos;
extern float ypos;

bool q1textured = false;
bool allowq1release = false;
bool q2textured = false;
bool allowq2release = false;
bool q3textured = false;
bool allowq3release = false;
bool q4textured = false;
bool allowq4release = false;
bool q5textured = false;
bool allowq5release = false;
bool activateTextInputGridX = false;
bool q1texturedY = false;
bool q2texturedY = false;
bool allowq2releaseY = false;
bool q3texturedY = false;
bool allowq3releaseY = false;
bool q4texturedY = false;
bool allowq4releaseY = false;
bool q5texturedY = false;
bool allowq5releaseY = false;
bool activateTextInputGridY = false;
float qEmpty = 0.99951171875f;
bool wasPressedLastFrame = false;

//this takes care of the numbers in the grid editor
std::vector<int> qXnumbers{};
std::vector<int> qYnumbers{};
int qx1{}, qx2{}, qx3{}, qx4{}, qx5{};
int qy1{}, qy2{}, qy3{}, qy4{}, qy5{};
int gridCellX{};
int gridCellY{};

bool shouldUpdateGrid = false;
bool shouldUpdateLines = false;
bool isGridLinesToggled = false;
bool initialPressCheckedEditor = false;
bool hoveringToggleGridButton = false;

struct Editor {

	void loadTexture() {
		glGenTextures(1, &editorTexture);
		glBindTexture(GL_TEXTURE_2D, editorTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(false);
		unsigned char* data = stbi_load("C:/Users/istra/Edenra/Edenra/images/AtlasEditor.png", &width, &height, &nrChannels, STBI_rgb_alpha);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load AtlasEditor.png" << std::endl;
		}
		stbi_image_free(data);
	}

	void populateEditor() {
		//Editor UI   (0)
		EditorVertices vertex;
		vertex.position[0] = glm::vec3(1500.0f, 1080.0f, 0.0f);  //top left
		vertex.position[1] = glm::vec3(1920.0f, 1080.0f, 0.0f);  //top right
		vertex.position[2] = glm::vec3(1920.0f, 0.0f, 0.0f);  //bottom right
		vertex.position[3] = glm::vec3(1500.0f, 0.0f, 0.0f);  //bottom left
		vertex.texture[0] = glm::vec2(0.0f, 0.0f); //top left
		vertex.texture[1] = glm::vec2(0.041015625f, 0.0f); //top right
		vertex.texture[2] = glm::vec2(0.041015625f, 0.10546875f); //bottom right
		vertex.texture[3] = glm::vec2(0.0f, 0.10546875f); //bottom left
		verticesEditor.push_back(vertex);
		//Text input 1	(1) X
		vertex.position[0] = glm::vec3(1700.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1716.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1716.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1700.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible   //23, 24
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible  //28, 29 ... etc.
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 2 (2) X
		vertex.position[0] = glm::vec3(1718.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1734.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1734.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1718.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 3	(3) X
		vertex.position[0] = glm::vec3(1736.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1752.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1752.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1736.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 4	(4) X
		vertex.position[0] = glm::vec3(1754.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1770.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1770.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1754.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 5 (5) X
		vertex.position[0] = glm::vec3(1772.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1788.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1788.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1772.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Selector for text input right (6) X
		vertex.position[0] = glm::vec3(1890.0f, 995.0f, 0.0f);
		vertex.position[1] = glm::vec3(1905.0f, 995.0f, 0.0f);
		vertex.position[2] = glm::vec3(1905.0f, 950.0f, 0.0f);
		vertex.position[3] = glm::vec3(1890.0f, 950.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Selector for text input left (6) X
		vertex.position[0] = glm::vec3(1515.125f, 995.0f, 0.0f);
		vertex.position[1] = glm::vec3(1530.0f, 995.0f, 0.0f);
		vertex.position[2] = glm::vec3(1530.0f, 950.0f, 0.0f);
		vertex.position[3] = glm::vec3(1515.125f, 950.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 1	(1) Y
		vertex.position[0] = glm::vec3(1700.0f, 931.0f, 0.0f);
		vertex.position[1] = glm::vec3(1716.0f, 931.0f, 0.0f);
		vertex.position[2] = glm::vec3(1716.0f, 903.0f, 0.0f);
		vertex.position[3] = glm::vec3(1700.0f, 903.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 2 (2) Y
		vertex.position[0] = glm::vec3(1718.0f, 931.0f, 0.0f);
		vertex.position[1] = glm::vec3(1734.0f, 931.0f, 0.0f);
		vertex.position[2] = glm::vec3(1734.0f, 903.0f, 0.0f);
		vertex.position[3] = glm::vec3(1718.0f, 903.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 3	(3) Y
		vertex.position[0] = glm::vec3(1736.0f, 931.0f, 0.0f);
		vertex.position[1] = glm::vec3(1752.0f, 931.0f, 0.0f);
		vertex.position[2] = glm::vec3(1752.0f, 903.0f, 0.0f);
		vertex.position[3] = glm::vec3(1736.0f, 903.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 4	(4) Y
		vertex.position[0] = glm::vec3(1754.0f, 931.0f, 0.0f);
		vertex.position[1] = glm::vec3(1770.0f, 931.0f, 0.0f);
		vertex.position[2] = glm::vec3(1770.0f, 903.0f, 0.0f);
		vertex.position[3] = glm::vec3(1754.0f, 903.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 5 (5) Y
		vertex.position[0] = glm::vec3(1772.0f, 931.0f, 0.0f);
		vertex.position[1] = glm::vec3(1788.0f, 931.0f, 0.0f);
		vertex.position[2] = glm::vec3(1788.0f, 903.0f, 0.0f);
		vertex.position[3] = glm::vec3(1772.0f, 903.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Selector for text input right (6) Y
		vertex.position[0] = glm::vec3(1890.0f, 940.0f, 0.0f);
		vertex.position[1] = glm::vec3(1905.0f, 940.0f, 0.0f);
		vertex.position[2] = glm::vec3(1905.0f, 895.0f, 0.0f);
		vertex.position[3] = glm::vec3(1890.0f, 895.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Selector for text input left (6) Y
		vertex.position[0] = glm::vec3(1515.125f, 940.0f, 0.0f);
		vertex.position[1] = glm::vec3(1530.0f, 940.0f, 0.0f);
		vertex.position[2] = glm::vec3(1530.0f, 895.0f, 0.0f);
		vertex.position[3] = glm::vec3(1515.125f, 895.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Back to Menu button
		vertex.position[0] = glm::vec3(1850.0f, 1050.0f, 0.0f);
		vertex.position[1] = glm::vec3(1885.0f, 1050.0f, 0.0f);
		vertex.position[2] = glm::vec3(1885.0f, 1015.0f, 0.0f);
		vertex.position[3] = glm::vec3(1850.0f, 1015.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Generate button - starts at index 323
		vertex.position[0] = glm::vec3(1600.0f, 825.0f, 0.0f);
		vertex.position[1] = glm::vec3(1830.0f, 825.0f, 0.0f);
		vertex.position[2] = glm::vec3(1830.0f, 780.0f, 0.0f);
		vertex.position[3] = glm::vec3(1600.0f, 780.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Grid Toggle Button
		vertex.position[0] = glm::vec3(1580.0f, 765.0f, 0.0f);
		vertex.position[1] = glm::vec3(1850.0f, 765.0f, 0.0f);
		vertex.position[2] = glm::vec3(1850.0f, 720.0f, 0.0f);
		vertex.position[3] = glm::vec3(1580.0f, 720.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//PUSH THEM ALL TO THE VECTOR - FLATTENING VERTICES
		for (auto& vertex : verticesEditor) {
			for (int i = 0; i < 4; i++) {
				flattenedVertices.push_back(vertex.position[i].x);
				flattenedVertices.push_back(vertex.position[i].y);
				flattenedVertices.push_back(vertex.position[i].z);
				flattenedVertices.push_back(vertex.texture[i].x);
				flattenedVertices.push_back(vertex.texture[i].y);
			}
		}
		EditorIndices index;
		//Editor UI
		index.indices[0] = 0; index.indices[1] = 1; index.indices[2] = 2;
		index.indices[3] = 0; index.indices[4] = 2; index.indices[5] = 3;
		indicesEditor.push_back(index);
		//Text Input 1 X
		index.indices[0] = 4; index.indices[1] = 5; index.indices[2] = 6;
		index.indices[3] = 4; index.indices[4] = 6; index.indices[5] = 7;
		indicesEditor.push_back(index);
		//Text Input 2 X
		index.indices[0] = 8; index.indices[1] = 9; index.indices[2] = 10;
		index.indices[3] = 8; index.indices[4] = 10; index.indices[5] = 11;
		indicesEditor.push_back(index);
		//Text Input 3 X
		index.indices[0] = 12; index.indices[1] = 13; index.indices[2] = 14;
		index.indices[3] = 12; index.indices[4] = 14; index.indices[5] = 15;
		indicesEditor.push_back(index);
		//Text Input 4 X
		index.indices[0] = 16; index.indices[1] = 17; index.indices[2] = 18;
		index.indices[3] = 16; index.indices[4] = 18; index.indices[5] = 19;
		indicesEditor.push_back(index);
		//Text Input 5 X
		index.indices[0] = 20; index.indices[1] = 21; index.indices[2] = 22;
		index.indices[3] = 20; index.indices[4] = 22; index.indices[5] = 23;
		indicesEditor.push_back(index);
		//Selector for text input right X
		index.indices[0] = 24; index.indices[1] = 25; index.indices[2] = 26;
		index.indices[3] = 24; index.indices[4] = 26; index.indices[5] = 27;
		indicesEditor.push_back(index);
		//Selector for text input left X
		index.indices[0] = 28; index.indices[1] = 29; index.indices[2] = 30;
		index.indices[3] = 28; index.indices[4] = 30; index.indices[5] = 31;
		indicesEditor.push_back(index);
		//Text Input 1 Y
		index.indices[0] = 32; index.indices[1] = 33; index.indices[2] = 34;
		index.indices[3] = 32; index.indices[4] = 34; index.indices[5] = 35;
		indicesEditor.push_back(index);
		//Text Input 2 Y
		index.indices[0] = 36; index.indices[1] = 37; index.indices[2] = 38;
		index.indices[3] = 36; index.indices[4] = 38; index.indices[5] = 39;
		indicesEditor.push_back(index);
		//Text Input 3 Y
		index.indices[0] = 40; index.indices[1] = 41; index.indices[2] = 42;
		index.indices[3] = 40; index.indices[4] = 42; index.indices[5] = 43;
		indicesEditor.push_back(index);
		//Text Input 4 Y
		index.indices[0] = 44; index.indices[1] = 45; index.indices[2] = 46;
		index.indices[3] = 44; index.indices[4] = 46; index.indices[5] = 47;
		indicesEditor.push_back(index);
		//Text Input 5 Y
		index.indices[0] = 48; index.indices[1] = 49; index.indices[2] = 50;
		index.indices[3] = 48; index.indices[4] = 50; index.indices[5] = 51;
		indicesEditor.push_back(index);
		//Selector for text input right Y
		index.indices[0] = 52; index.indices[1] = 53; index.indices[2] = 54;
		index.indices[3] = 52; index.indices[4] = 54; index.indices[5] = 55;
		indicesEditor.push_back(index);
		//Selector for text input left Y
		index.indices[0] = 56; index.indices[1] = 57; index.indices[2] = 58;
		index.indices[3] = 56; index.indices[4] = 58; index.indices[5] = 59;
		indicesEditor.push_back(index);
		//Back to menu button
		index.indices[0] = 60; index.indices[1] = 61; index.indices[2] = 62;
		index.indices[3] = 60; index.indices[4] = 62; index.indices[5] = 63;
		indicesEditor.push_back(index);
		//Generate Button
		index.indices[0] = 64; index.indices[1] = 65; index.indices[2] = 66;
		index.indices[3] = 64; index.indices[4] = 66; index.indices[5] = 67;
		indicesEditor.push_back(index);
		//Grid Toggle Button
		index.indices[0] = 68; index.indices[1] = 69; index.indices[2] = 70;
		index.indices[3] = 68; index.indices[4] = 70; index.indices[5] = 71;
		indicesEditor.push_back(index);
		//PUSH THEM ALL TO THE VECTOR - FLATTENING INDICES
		for (auto& index : indicesEditor) {
			for (int i = 0; i < 6; i++) {
				flattenedIndices.push_back(index.indices[i]);
			}
		}
	}

	void interactiveEditor(GLFWwindow* window) {
		if (buttonIsPressed && !initialPressCheckedEditor) {
			if (hoveringToggleGridButton && !isGridLinesToggled) {
				isGridLinesToggled = true;
				shouldUpdateLines = true;
			}
			else if (hoveringToggleGridButton && isGridLinesToggled) {
				isGridLinesToggled = false;
			}
			initialPressCheckedEditor = true;
		}
		if (buttonIsReleased) {
			initialPressCheckedEditor = false;
		}
		//if in range of Grid Size X
		if (xpos > 1667.0f && xpos < 1884.0f && ypos > 956.0f && ypos < 990.0f) {
			if (buttonIsPressed) {
				activateTextInputGridX = true;
			}
		}
		else {
			if (buttonIsPressed) {
				activateTextInputGridX = false;
			}
		}
		//if in range of Grid Size Y
		if (xpos > 1667.0f && xpos < 1884.0f && ypos > 902.0f && ypos < 936.0f) {
			if (buttonIsPressed) {
				activateTextInputGridY = true;
			}
		}
		else {
			if (buttonIsPressed) {
				activateTextInputGridY = false;
			}
		}
		//generate button
		if (xpos > 1591.0f && xpos < 1828.0f && ypos > 782.0f && ypos < 824.0f) {
			flattenedVertices[323] = 0.0478515625f;   //top left
			flattenedVertices[324] = 0.00244140625f;
			flattenedVertices[328] = 0.0703125f;    //top right
			flattenedVertices[329] = 0.00244140625f;
			flattenedVertices[333] = 0.0703125f;    //bottom right
			flattenedVertices[334] = 0.0068359375f;
			flattenedVertices[338] = 0.0478515625f;   //bottom left
			flattenedVertices[339] = 0.0068359375f;
		}
		else {
			flattenedVertices[323] = 0.99951171875f;   //top left
			flattenedVertices[324] = 0.99951171875f;
			flattenedVertices[328] = 1.0f;    //top right
			flattenedVertices[329] = 0.99951171875f;
			flattenedVertices[333] = 1.0f;    //bottom right
			flattenedVertices[334] = 1.0f;
			flattenedVertices[338] = 0.99951171875f;   //bottom left
			flattenedVertices[339] = 0.99951171875f;
		}
		//grid toggle button
		if (xpos > 1573.0f && xpos < 1846.0f && ypos > 723.0f && ypos < 763.0f) {
			hoveringToggleGridButton = true;
			flattenedVertices[343] = 0.0498046875f;   //top left
			flattenedVertices[344] = 0.0146484375f;
			flattenedVertices[348] = 0.076171875f;    //top right
			flattenedVertices[349] = 0.0146484375f;
			flattenedVertices[353] = 0.076171875f;    //bottom right
			flattenedVertices[354] = 0.01904296875f;
			flattenedVertices[358] = 0.0498046875f;   //bottom left
			flattenedVertices[359] = 0.01904296875f;
		}
		else {
			hoveringToggleGridButton = false;
			flattenedVertices[343] = 0.99951171875f;   //top left
			flattenedVertices[344] = 0.99951171875f;
			flattenedVertices[348] = 1.0f;    //top right
			flattenedVertices[349] = 0.99951171875f;
			flattenedVertices[353] = 1.0f;    //bottom right
			flattenedVertices[354] = 1.0f;
			flattenedVertices[358] = 0.99951171875f;   //bottom left
			flattenedVertices[359] = 0.99951171875f;
		}
		//Back to Menu button
		if (xpos > 1851.0f && xpos < 1882.0f && ypos > 1017.0f && ypos < 1050.0f) {
			flattenedVertices[303] = 0.0419921875f;   //top left
			flattenedVertices[304] = 0.00341796875f;
			flattenedVertices[308] = 0.04541015625f;    //top right
			flattenedVertices[309] = 0.00341796875f;
			flattenedVertices[313] = 0.04541015625f;    //bottom right
			flattenedVertices[314] = 0.0068359375f;
			flattenedVertices[318] = 0.0419921875f;   //bottom left
			flattenedVertices[319] = 0.0068359375f;
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				//ask the user if he wants to save the map or not
				gameState = gameMenu;
			}
		}
		else {
			flattenedVertices[303] = 0.99951171875f;   //top left
			flattenedVertices[304] = 0.99951171875f;
			flattenedVertices[308] = 1.0f;    //top right
			flattenedVertices[309] = 0.99951171875f;
			flattenedVertices[313] = 1.0f;    //bottom right
			flattenedVertices[314] = 1.0f;
			flattenedVertices[318] = 0.99951171875f;   //bottom left
			flattenedVertices[319] = 0.99951171875f;
		}
		//GRID X
		if (activateTextInputGridX) {

			flattenedVertices[123] = 0.046875f;   //top left
			flattenedVertices[124] = 0.01123046875f;
			flattenedVertices[128] = 0.04833984375f;    //top right
			flattenedVertices[129] = 0.01123046875f;
			flattenedVertices[133] = 0.04833984375f;    //bottom right
			flattenedVertices[134] = 0.013671875f;
			flattenedVertices[138] = 0.046875;   //bottom left
			flattenedVertices[139] = 0.013671875f;

			flattenedVertices[143] = 0.046875f;   //top left
			flattenedVertices[144] = 0.01123046875f;
			flattenedVertices[148] = 0.04833984375f;    //top right
			flattenedVertices[149] = 0.01123046875f;
			flattenedVertices[153] = 0.04833984375f;    //bottom right
			flattenedVertices[154] = 0.013671875f;
			flattenedVertices[158] = 0.046875;   //bottom left
			flattenedVertices[159] = 0.013671875f;
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);

			//Quad1
			if ((key1Pressed && !q1textured) || (key1Pressed && q1textured && flattenedVertices[23] == qEmpty)) {
				//verticesEditor.at(1).texture[0];
				flattenedVertices[23] = 0.04833984375f;   //top left
				flattenedVertices[24] = 0.0f;
				//verticesEditor.at(1).texture[1];
				flattenedVertices[28] = 0.04931640625f;    //top right
				flattenedVertices[29] = 0.0f;
				//verticesEditor.at(1).texture[2];
				flattenedVertices[33] = 0.04931640625f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				//verticesEditor.at(1).texture[3];
				flattenedVertices[38] = 0.04833984375f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && !q1textured) {
				flattenedVertices[23] = 0.05224609375f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.0537109375f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.0537109375f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.05224609375f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && !q1textured) {
				flattenedVertices[23] = 0.0537109375f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.05517578125f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.05517578125f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.0537109375f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && !q1textured) {
				flattenedVertices[23] = 0.0595703125f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.06103515625f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.06103515625f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.0595703125f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && !q1textured) {
				flattenedVertices[23] = 0.05810546875f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.0595703125f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.0595703125f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.05810546875f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && !q1textured) {
				flattenedVertices[23] = 0.05078125f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.05224609375f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.05224609375f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.05078125f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && !q1textured) {
				flattenedVertices[23] = 0.04931640625f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.05078125f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.05078125f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.04931640625f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && !q1textured) {
				flattenedVertices[23] = 0.056640625f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.05810546875f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.05810546875f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.056640625f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && !q1textured) {
				flattenedVertices[23] = 0.046875f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.04833984375f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.04833984375f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.046875f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && !q1textured) {
				flattenedVertices[23] = 0.05517578125f;   //top left
				flattenedVertices[24] = 0.0f;
				flattenedVertices[28] = 0.056640625f;    //top right
				flattenedVertices[29] = 0.0f;
				flattenedVertices[33] = 0.056640625f;    //bottom right
				flattenedVertices[34] = 0.00244140625f;
				flattenedVertices[38] = 0.05517578125f;   //bottom left
				flattenedVertices[39] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key1Released && !q1textured && flattenedVertices[23] != qEmpty || key2Released && !q1textured && flattenedVertices[23] != qEmpty || key3Released && !q1textured && flattenedVertices[23] != qEmpty || key4Released && !q1textured && flattenedVertices[23] != qEmpty || key5Released
				&& !q1textured && flattenedVertices[23] != qEmpty || key6Released && !q1textured && flattenedVertices[23] != qEmpty || key7Released && !q1textured && flattenedVertices[23] != qEmpty || key8Released && !q1textured && flattenedVertices[23] != qEmpty
				|| key9Released && !q1textured && flattenedVertices[23] != qEmpty || key0Released && !q1textured && flattenedVertices[23] != qEmpty) {
				q1textured = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 1 delete method
			if (keyBackspacePressed && q1textured && !q2textured) {
				flattenedVertices[23] = 0.99951171875f;
				flattenedVertices[24] = 0.99951171875f;
				flattenedVertices[28] = 1.0f;
				flattenedVertices[29] = 0.99951171875f;
				flattenedVertices[33] = 1.0f;
				flattenedVertices[34] = 1.0f;
				flattenedVertices[38] = 0.99951171875f;
				flattenedVertices[39] = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[23] == 0.99951171875f) {
				q1textured = false;
			}
			//Quad2
			if (key1Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.04833984375f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.04931640625f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.04931640625f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.04833984375f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.05224609375f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.0537109375f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.0537109375f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.05224609375f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.0537109375f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.05517578125f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.05517578125f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.0537109375f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.0595703125f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.06103515625f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.06103515625f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.0595703125f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.05810546875f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.0595703125f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.0595703125f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.05810546875f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.05078125f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.05224609375f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.05224609375f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.05078125f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.04931640625f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.05078125f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.05078125f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.04931640625f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.056640625f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.05810546875f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.05810546875f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.056640625f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.046875f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.04833984375f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.04833984375f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.046875f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q1textured && !q2textured) {
				flattenedVertices[43] = 0.05517578125f;   //top left
				flattenedVertices[44] = 0.0f;
				flattenedVertices[48] = 0.056640625f;    //top right
				flattenedVertices[49] = 0.0f;
				flattenedVertices[53] = 0.056640625f;    //bottom right
				flattenedVertices[54] = 0.00244140625f;
				flattenedVertices[58] = 0.05517578125f;   //bottom left
				flattenedVertices[59] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2release = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q1textured && allowq2release && !q2textured) || (key2Released && q1textured && allowq2release && !q2textured)
				|| (key3Released && q1textured && allowq2release && !q2textured) || (key4Released && q1textured && allowq2release && !q2textured)
				|| (key5Released && q1textured && allowq2release && !q2textured) || (key6Released && q1textured && allowq2release && !q2textured)
				|| (key7Released && q1textured && allowq2release && !q2textured) || (key8Released && q1textured && allowq2release && !q2textured)
				|| (key9Released && q1textured && allowq2release && !q2textured) || (key0Released && q1textured && allowq2release && !q2textured)) {
				q2textured = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 2 delete method
			if (keyBackspacePressed && q2textured && !q3textured) {
				flattenedVertices.at(43) = 0.99951171875f;
				flattenedVertices.at(44) = 0.99951171875f;
				flattenedVertices.at(48) = 1.0f;
				flattenedVertices.at(49) = 0.99951171875f;
				flattenedVertices.at(53) = 1.0f;
				flattenedVertices.at(54) = 1.0f;
				flattenedVertices.at(58) = 0.99951171875f;
				flattenedVertices.at(59) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[43] == 0.99951171875f) {
				q2textured = false;
				allowq2release = false;
			}
			//Quad3
			if (key1Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.04833984375f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.04931640625f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.04931640625f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.04833984375f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.05224609375f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.0537109375f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.0537109375f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.05224609375f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.0537109375f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.05517578125f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.05517578125f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.0537109375f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.0595703125f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.06103515625f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.06103515625f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.0595703125f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.05810546875f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.0595703125f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.0595703125f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.05810546875f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.05078125f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.05224609375f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.05224609375f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.05078125f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.04931640625f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.05078125f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.05078125f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.04931640625f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.056640625f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.05810546875f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.05810546875f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.056640625f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.046875f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.04833984375f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.04833984375f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.046875f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q2textured && !q3textured) {
				flattenedVertices[63] = 0.05517578125f;   //top left
				flattenedVertices[64] = 0.0f;
				flattenedVertices[68] = 0.056640625f;    //top right
				flattenedVertices[69] = 0.0f;
				flattenedVertices[73] = 0.056640625f;    //bottom right
				flattenedVertices[74] = 0.00244140625f;
				flattenedVertices[78] = 0.05517578125f;   //bottom left
				flattenedVertices[79] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3release = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q2textured && allowq3release && !q3textured) || (key2Released && q2textured && allowq3release && !q3textured)
				|| (key3Released && q2textured && allowq3release && !q3textured) || (key4Released && q2textured && allowq3release && !q3textured)
				|| (key5Released && q2textured && allowq3release && !q3textured) || (key6Released && q2textured && allowq3release && !q3textured)
				|| (key7Released && q2textured && allowq3release && !q3textured) || (key8Released && q2textured && allowq3release && !q3textured)
				|| (key9Released && q2textured && allowq3release && !q3textured) || (key0Released && q2textured && allowq3release && !q3textured)) {
				q3textured = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 3 delete method
			if (keyBackspacePressed && q3textured && !q4textured) {
				flattenedVertices.at(63) = 0.99951171875f;
				flattenedVertices.at(64) = 0.99951171875f;
				flattenedVertices.at(68) = 1.0f;
				flattenedVertices.at(69) = 0.99951171875f;
				flattenedVertices.at(73) = 1.0f;
				flattenedVertices.at(74) = 1.0f;
				flattenedVertices.at(78) = 0.99951171875f;
				flattenedVertices.at(79) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[63] == 0.99951171875f) {
				q3textured = false;
				allowq3release = false;
			}
			//Quad4
			if (key1Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.04833984375f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.04931640625f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.04931640625f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.04833984375f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
			}
			else if (key2Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.05224609375f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.0537109375f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.0537109375f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.05224609375f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.0537109375f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.05517578125f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.05517578125f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.0537109375f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.0595703125f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.06103515625f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.06103515625f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.0595703125f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.05810546875f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.0595703125f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.0595703125f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.05810546875f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.05078125f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.05224609375f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.05224609375f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.05078125f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.04931640625f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.05078125f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.05078125f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.04931640625f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.056640625f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.05810546875f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.05810546875f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.056640625f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.046875f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.04833984375f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.04833984375f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.046875f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q3textured && !q4textured) {
				flattenedVertices[83] = 0.05517578125f;   //top left
				flattenedVertices[84] = 0.0f;
				flattenedVertices[88] = 0.056640625f;    //top right
				flattenedVertices[89] = 0.0f;
				flattenedVertices[93] = 0.056640625f;    //bottom right
				flattenedVertices[94] = 0.00244140625f;
				flattenedVertices[98] = 0.05517578125f;   //bottom left
				flattenedVertices[99] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4release = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q3textured && allowq4release && !q4textured) || (key2Released && q3textured && allowq4release && !q4textured)
				|| (key3Released && q3textured && allowq4release && !q4textured) || (key4Released && q3textured && allowq4release && !q4textured)
				|| (key5Released && q3textured && allowq4release && !q4textured) || (key6Released && q3textured && allowq4release && !q4textured)
				|| (key7Released && q3textured && allowq4release && !q4textured) || (key8Released && q3textured && allowq4release && !q4textured)
				|| (key9Released && q3textured && allowq4release && !q4textured) || (key0Released && q3textured && allowq4release && !q4textured)) {
				q4textured = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 4 delete method
			if (keyBackspacePressed && q4textured && !q5textured) {
				flattenedVertices.at(83) = 0.99951171875f;
				flattenedVertices.at(84) = 0.99951171875f;
				flattenedVertices.at(88) = 1.0f;
				flattenedVertices.at(89) = 0.99951171875f;
				flattenedVertices.at(93) = 1.0f;
				flattenedVertices.at(94) = 1.0f;
				flattenedVertices.at(98) = 0.99951171875f;
				flattenedVertices.at(99) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[83] == 0.99951171875f) {
				q4textured = false;
				allowq4release = false;
			}
			//Quad5
			if (key1Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.04833984375f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.04931640625f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.04931640625f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.04833984375f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
			}
			else if (key2Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.05224609375f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.0537109375f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.0537109375f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.05224609375f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.0537109375f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.05517578125f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.05517578125f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.0537109375f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.0595703125f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.06103515625f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.06103515625f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.0595703125f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.05810546875f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.0595703125f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.0595703125f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.05810546875f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.05078125f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.05224609375f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.05224609375f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.05078125f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.04931640625f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.05078125f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.05078125f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.04931640625f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.056640625f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.05810546875f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.05810546875f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.056640625f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.046875f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.04833984375f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.04833984375f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.046875f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q4textured && !q5textured) {
				flattenedVertices[103] = 0.05517578125f;   //top left
				flattenedVertices[104] = 0.0f;
				flattenedVertices[108] = 0.056640625f;    //top right
				flattenedVertices[109] = 0.0f;
				flattenedVertices[113] = 0.056640625f;    //bottom right
				flattenedVertices[114] = 0.00244140625f;
				flattenedVertices[118] = 0.05517578125f;   //bottom left
				flattenedVertices[119] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5release = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q3textured && allowq5release && !q5textured) || (key2Released && q3textured && allowq5release && !q5textured)
				|| (key3Released && q3textured && allowq5release && !q5textured) || (key4Released && q3textured && allowq5release && !q5textured)
				|| (key5Released && q3textured && allowq5release && !q5textured) || (key6Released && q3textured && allowq5release && !q5textured)
				|| (key7Released && q3textured && allowq5release && !q5textured) || (key8Released && q3textured && allowq5release && !q5textured)
				|| (key9Released && q3textured && allowq5release && !q5textured) || (key0Released && q3textured && allowq5release && !q5textured)) {
				q5textured = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 5 delete method
			if (keyBackspacePressed && q5textured) {
				flattenedVertices[103] = 0.99951171875f;
				flattenedVertices[104] = 0.99951171875f;
				flattenedVertices[108] = 1.0f;
				flattenedVertices[109] = 0.99951171875f;
				flattenedVertices[113] = 1.0f;
				flattenedVertices[114] = 1.0f;
				flattenedVertices[118] = 0.99951171875f;
				flattenedVertices[119] = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[103] == 0.99951171875f) {
				q5textured = false;
				allowq5release = false;
			}
		}
		else {
			flattenedVertices[123] = 0.99951171875f;   //top left
			flattenedVertices[124] = 0.99951171875f;
			flattenedVertices[128] = 1.0f;    //top right
			flattenedVertices[129] = 0.99951171875f;
			flattenedVertices[133] = 1.0f;    //bottom right
			flattenedVertices[134] = 1.0f;
			flattenedVertices[138] = 0.99951171875f;   //bottom left
			flattenedVertices[139] = 1.0f;

			flattenedVertices[143] = 0.99951171875f;   //top left
			flattenedVertices[144] = 0.99951171875f;
			flattenedVertices[148] = 1.0f;    //top right
			flattenedVertices[149] = 0.99951171875f;
			flattenedVertices[153] = 1.0f;    //bottom right
			flattenedVertices[154] = 1.0f;
			flattenedVertices[158] = 0.99951171875f;   //bottom left
			flattenedVertices[159] = 1.0f;
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
		}
		//GRID Y
		if (activateTextInputGridY) {
			flattenedVertices[263] = 0.046875f;   //top left
			flattenedVertices[264] = 0.01123046875f;
			flattenedVertices[268] = 0.04833984375f;    //top right
			flattenedVertices[269] = 0.01123046875f;
			flattenedVertices[273] = 0.04833984375f;    //bottom right
			flattenedVertices[274] = 0.013671875f;
			flattenedVertices[278] = 0.046875;   //bottom left
			flattenedVertices[279] = 0.013671875f;

			flattenedVertices[283] = 0.046875f;   //top left
			flattenedVertices[284] = 0.01123046875f;
			flattenedVertices[288] = 0.04833984375f;    //top right
			flattenedVertices[289] = 0.01123046875f;
			flattenedVertices[293] = 0.04833984375f;    //bottom right
			flattenedVertices[294] = 0.013671875f;
			flattenedVertices[298] = 0.046875;   //bottom left
			flattenedVertices[299] = 0.013671875f;
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			//Quad1
			if ((key1Pressed && !q1texturedY) || (key1Pressed && q1texturedY && flattenedVertices[163] == qEmpty)) {
				//verticesEditor.at(1).texture[0];
				flattenedVertices[163] = 0.04833984375f;   //top left
				flattenedVertices[164] = 0.0f;
				//verticesEditor.at(1).texture[1];
				flattenedVertices[168] = 0.04931640625f;    //top right
				flattenedVertices[169] = 0.0f;
				//verticesEditor.at(1).texture[2];
				flattenedVertices[173] = 0.04931640625f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				//verticesEditor.at(1).texture[3];
				flattenedVertices[178] = 0.04833984375f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.05224609375f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.0537109375f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.0537109375f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.05224609375f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.0537109375f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.05517578125f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.05517578125f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.0537109375f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.0595703125f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.06103515625f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.06103515625f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.0595703125f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.05810546875f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.0595703125f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.0595703125f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.05810546875f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.05078125f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.05224609375f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.05224609375f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.05078125f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.04931640625f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.05078125f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.05078125f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.04931640625f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.056640625f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.05810546875f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.05810546875f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.056640625f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.046875f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.04833984375f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.04833984375f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.046875f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && !q1texturedY) {
				flattenedVertices[163] = 0.05517578125f;   //top left
				flattenedVertices[164] = 0.0f;
				flattenedVertices[168] = 0.056640625f;    //top right
				flattenedVertices[169] = 0.0f;
				flattenedVertices[173] = 0.056640625f;    //bottom right
				flattenedVertices[174] = 0.00244140625f;
				flattenedVertices[178] = 0.05517578125f;   //bottom left
				flattenedVertices[179] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				keyBackspaceReleased = false;
			}
			else if (key1Released && !q1texturedY && flattenedVertices[163] != qEmpty || key2Released && !q1texturedY && flattenedVertices[163] != qEmpty || key3Released && !q1texturedY && flattenedVertices[163] != qEmpty || key4Released && !q1texturedY && flattenedVertices[163] != qEmpty
				|| key5Released && !q1texturedY && flattenedVertices[163] != qEmpty || key6Released && !q1texturedY && flattenedVertices[163] != qEmpty || key7Released && !q1texturedY && flattenedVertices[163] != qEmpty ||
				key8Released && !q1texturedY && flattenedVertices[163] != qEmpty || key9Released && !q1texturedY && flattenedVertices[163] != qEmpty || key0Released && !q1texturedY && flattenedVertices[163] != qEmpty) {
				q1texturedY = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 1 delete method
			if (keyBackspacePressed && q1texturedY && !q2texturedY) {
				flattenedVertices.at(163) = 0.99951171875f;
				flattenedVertices.at(164) = 0.99951171875f;
				flattenedVertices.at(168) = 1.0f;
				flattenedVertices.at(169) = 0.99951171875f;
				flattenedVertices.at(173) = 1.0f;
				flattenedVertices.at(174) = 1.0f;
				flattenedVertices.at(178) = 0.99951171875f;
				flattenedVertices.at(179) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[163] == 0.99951171875f) {
				q1texturedY = false;
			}
			//Quad2
			if (key1Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.04833984375f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.04931640625f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.04931640625f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.04833984375f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.05224609375f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.0537109375f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.0537109375f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.05224609375f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.0537109375f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.05517578125f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.05517578125f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.0537109375f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.0595703125f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.06103515625f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.06103515625f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.0595703125f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.05810546875f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.0595703125f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.0595703125f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.05810546875f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.05078125f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.05224609375f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.05224609375f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.05078125f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.04931640625f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.05078125f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.05078125f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.04931640625f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.056640625f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.05810546875f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.05810546875f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.056640625f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.046875f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.04833984375f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.04833984375f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.046875f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q1texturedY && !q2texturedY) {
				flattenedVertices[183] = 0.05517578125f;   //top left
				flattenedVertices[184] = 0.0f;
				flattenedVertices[188] = 0.056640625f;    //top right
				flattenedVertices[189] = 0.0f;
				flattenedVertices[193] = 0.056640625f;    //bottom right
				flattenedVertices[194] = 0.00244140625f;
				flattenedVertices[198] = 0.05517578125f;   //bottom left
				flattenedVertices[199] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq2releaseY = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q1texturedY && allowq2releaseY && !q2texturedY) || (key2Released && q1texturedY && allowq2releaseY && !q2texturedY)
				|| (key3Released && q1texturedY && allowq2releaseY && !q2texturedY) || (key4Released && q1texturedY && allowq2releaseY && !q2texturedY)
				|| (key5Released && q1texturedY && allowq2releaseY && !q2texturedY) || (key6Released && q1texturedY && allowq2releaseY && !q2texturedY)
				|| (key7Released && q1texturedY && allowq2releaseY && !q2texturedY) || (key8Released && q1texturedY && allowq2releaseY && !q2texturedY)
				|| (key9Released && q1texturedY && allowq2releaseY && !q2texturedY) || (key0Released && q1texturedY && allowq2releaseY && !q2texturedY)) {
				q2texturedY = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 2 delete method
			if (keyBackspacePressed && q2texturedY && !q3texturedY) {
				flattenedVertices.at(183) = 0.99951171875f;
				flattenedVertices.at(184) = 0.99951171875f;
				flattenedVertices.at(188) = 1.0f;
				flattenedVertices.at(189) = 0.99951171875f;
				flattenedVertices.at(193) = 1.0f;
				flattenedVertices.at(194) = 1.0f;
				flattenedVertices.at(198) = 0.99951171875f;
				flattenedVertices.at(199) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[183] == 0.99951171875f) {
				q2texturedY = false;
				allowq2releaseY = false;
			}
			//Quad3
			if (key1Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.04833984375f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.04931640625f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.04931640625f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.04833984375f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.05224609375f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.0537109375f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.0537109375f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.05224609375f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.0537109375f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.05517578125f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.05517578125f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.0537109375f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.0595703125f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.06103515625f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.06103515625f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.0595703125f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.05810546875f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.0595703125f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.0595703125f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.05810546875f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.05078125f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.05224609375f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.05224609375f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.05078125f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.04931640625f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.05078125f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.05078125f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.04931640625f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.056640625f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.05810546875f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.05810546875f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.056640625f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.046875f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.04833984375f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.04833984375f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.046875f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q2texturedY && !q3texturedY) {
				flattenedVertices[203] = 0.05517578125f;   //top left
				flattenedVertices[204] = 0.0f;
				flattenedVertices[208] = 0.056640625f;    //top right
				flattenedVertices[209] = 0.0f;
				flattenedVertices[213] = 0.056640625f;    //bottom right
				flattenedVertices[214] = 0.00244140625f;
				flattenedVertices[218] = 0.05517578125f;   //bottom left
				flattenedVertices[219] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq3releaseY = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q2texturedY && allowq3releaseY && !q3texturedY) || (key2Released && q2texturedY && allowq3releaseY && !q3texturedY)
				|| (key3Released && q2texturedY && allowq3releaseY && !q3texturedY) || (key4Released && q2texturedY && allowq3releaseY && !q3texturedY)
				|| (key5Released && q2texturedY && allowq3releaseY && !q3texturedY) || (key6Released && q2texturedY && allowq3releaseY && !q3texturedY)
				|| (key7Released && q2texturedY && allowq3releaseY && !q3texturedY) || (key8Released && q2texturedY && allowq3releaseY && !q3texturedY)
				|| (key9Released && q2texturedY && allowq3releaseY && !q3texturedY) || (key0Released && q2texturedY && allowq3releaseY && !q3texturedY)) {
				q3texturedY = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 3 delete method
			if (keyBackspacePressed && q3texturedY && !q4texturedY) {
				flattenedVertices.at(203) = 0.99951171875f;
				flattenedVertices.at(204) = 0.99951171875f;
				flattenedVertices.at(208) = 1.0f;
				flattenedVertices.at(209) = 0.99951171875f;
				flattenedVertices.at(213) = 1.0f;
				flattenedVertices.at(214) = 1.0f;
				flattenedVertices.at(218) = 0.99951171875f;
				flattenedVertices.at(219) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[203] == 0.99951171875f) {
				q3texturedY = false;
				allowq3releaseY = false;
			}
			//Quad4
			if (key1Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.04833984375f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.04931640625f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.04931640625f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.04833984375f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.05224609375f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.0537109375f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.0537109375f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.05224609375f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.0537109375f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.05517578125f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.05517578125f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.0537109375f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.0595703125f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.06103515625f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.06103515625f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.0595703125f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.05810546875f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.0595703125f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.0595703125f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.05810546875f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.05078125f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.05224609375f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.05224609375f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.05078125f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.04931640625f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.05078125f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.05078125f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.04931640625f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.056640625f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.05810546875f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.05810546875f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.056640625f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.046875f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.04833984375f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.04833984375f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.046875f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q3texturedY && !q4texturedY) {
				flattenedVertices[223] = 0.05517578125f;   //top left
				flattenedVertices[224] = 0.0f;
				flattenedVertices[228] = 0.056640625f;    //top right
				flattenedVertices[229] = 0.0f;
				flattenedVertices[233] = 0.056640625f;    //bottom right
				flattenedVertices[234] = 0.00244140625f;
				flattenedVertices[238] = 0.05517578125f;   //bottom left
				flattenedVertices[239] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq4releaseY = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q3texturedY && allowq4releaseY && !q4texturedY) || (key2Released && q3texturedY && allowq4releaseY && !q4texturedY)
				|| (key3Released && q3texturedY && allowq4releaseY && !q4texturedY) || (key4Released && q3texturedY && allowq4releaseY && !q4texturedY)
				|| (key5Released && q3texturedY && allowq4releaseY && !q4texturedY) || (key6Released && q3texturedY && allowq4releaseY && !q4texturedY)
				|| (key7Released && q3texturedY && allowq4releaseY && !q4texturedY) || (key8Released && q3texturedY && allowq4releaseY && !q4texturedY)
				|| (key9Released && q3texturedY && allowq4releaseY && !q4texturedY) || (key0Released && q3texturedY && allowq4releaseY && !q4texturedY)) {
				q4texturedY = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 4 delete method
			if (keyBackspacePressed && q4texturedY && !q5texturedY) {
				flattenedVertices.at(223) = 0.99951171875f;
				flattenedVertices.at(224) = 0.99951171875f;
				flattenedVertices.at(228) = 1.0f;
				flattenedVertices.at(229) = 0.99951171875f;
				flattenedVertices.at(233) = 1.0f;
				flattenedVertices.at(234) = 1.0f;
				flattenedVertices.at(238) = 0.99951171875f;
				flattenedVertices.at(239) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[223] == 0.99951171875f) {
				q4texturedY = false;
				allowq4releaseY = false;
			}
			//Quad 5
			if (key1Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.04833984375f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.04931640625f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.04931640625f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.04833984375f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key2Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.05224609375f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.0537109375f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.0537109375f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.05224609375f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key3Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.0537109375f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.05517578125f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.05517578125f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.0537109375f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key4Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.0595703125f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.06103515625f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.06103515625f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.0595703125f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key5Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.05810546875f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.0595703125f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.0595703125f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.05810546875f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key6Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.05078125f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.05224609375f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.05224609375f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.05078125f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key7Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.04931640625f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.05078125f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.05078125f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.04931640625f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key8Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.056640625f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.05810546875f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.05810546875f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.056640625f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key9Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.046875f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.04833984375f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.04833984375f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.046875f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if (key0Pressed && q4texturedY && !q5texturedY) {
				flattenedVertices[243] = 0.05517578125f;   //top left
				flattenedVertices[244] = 0.0f;
				flattenedVertices[248] = 0.056640625f;    //top right
				flattenedVertices[249] = 0.0f;
				flattenedVertices[253] = 0.056640625f;    //bottom right
				flattenedVertices[254] = 0.00244140625f;
				flattenedVertices[258] = 0.05517578125f;   //bottom left
				flattenedVertices[259] = 0.00244140625f;
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
				allowq5releaseY = true;
				keyBackspaceReleased = false;
			}
			else if ((key1Released && q4texturedY && allowq5releaseY && !q5texturedY) || (key2Released && q4texturedY && allowq5releaseY && !q5texturedY)
				|| (key3Released && q4texturedY && allowq5releaseY && !q5texturedY) || (key4Released && q4texturedY && allowq5releaseY && !q5texturedY)
				|| (key5Released && q4texturedY && allowq5releaseY && !q5texturedY) || (key6Released && q4texturedY && allowq5releaseY && !q5texturedY)
				|| (key7Released && q4texturedY && allowq5releaseY && !q5texturedY) || (key8Released && q4texturedY && allowq5releaseY && !q5texturedY)
				|| (key9Released && q4texturedY && allowq5releaseY && !q5texturedY) || (key0Released && q4texturedY && allowq5releaseY && !q5texturedY)) {
				q5texturedY = true;
				key1Released = false;
				key2Released = false;
				key3Released = false;
				key4Released = false;
				key5Released = false;
				key6Released = false;
				key7Released = false;
				key8Released = false;
				key9Released = false;
				key0Released = false;
			}
			//Quad 5 delete method
			if (keyBackspacePressed && q5texturedY) {
				flattenedVertices.at(243) = 0.99951171875f;
				flattenedVertices.at(244) = 0.99951171875f;
				flattenedVertices.at(248) = 1.0f;
				flattenedVertices.at(249) = 0.99951171875f;
				flattenedVertices.at(253) = 1.0f;
				flattenedVertices.at(254) = 1.0f;
				flattenedVertices.at(258) = 0.99951171875f;
				flattenedVertices.at(259) = 1.0;
			}
			else if (keyBackspaceReleased && flattenedVertices[243] == 0.99951171875f) {
				q5texturedY = false;
				allowq5releaseY = false;
			}
		}
		else {
			flattenedVertices[263] = 0.99951171875f;   //top left
			flattenedVertices[264] = 0.99951171875f;
			flattenedVertices[268] = 1.0f;    //top right
			flattenedVertices[269] = 0.99951171875f;
			flattenedVertices[273] = 1.0f;    //bottom right
			flattenedVertices[274] = 1.0f;
			flattenedVertices[278] = 0.99951171875f;   //bottom left
			flattenedVertices[279] = 1.0;

			flattenedVertices[283] = 0.99951171875f;   //top left
			flattenedVertices[284] = 0.99951171875f;
			flattenedVertices[288] = 1.0f;    //top right
			flattenedVertices[289] = 0.99951171875f;
			flattenedVertices[293] = 1.0f;    //bottom right
			flattenedVertices[294] = 1.0f;
			flattenedVertices[298] = 0.99951171875f;   //bottom left
			flattenedVertices[299] = 1.0;
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
		}
	}

	void assignValuesGrid() {
		if (xpos > 1591.0f && xpos < 1828.0f && ypos > 782.0f && ypos < 824.0f) {
			if (buttonIsPressed && !wasPressedLastFrame) {
				qXnumbers.clear();
				qYnumbers.clear();
				gridCellX = 0;
				gridCellY = 0;
				//GRID X
				//First quad number
				if (flattenedVertices[23] == 0.04833984375f) {
					qx1 = 1;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.05224609375f) {
					qx1 = 2;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.0537109375f) {
					qx1 = 3;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.0595703125f) {
					qx1 = 4;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.05810546875f) {
					qx1 = 5;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.05078125f) {
					qx1 = 6;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.04931640625f) {
					qx1 = 7;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.056640625f) {
					qx1 = 8;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.046875f) {
					qx1 = 9;
					qXnumbers.push_back(qx1);
				}
				else if (flattenedVertices[23] == 0.05517578125f) {
					qx1 = 0;
					qXnumbers.push_back(qx1);
				}
				else {
					//do nothing
				}
				//Second quad number
				if (flattenedVertices[43] == 0.04833984375f) {
					qx2 = 1;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.05224609375f) {
					qx2 = 2;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.0537109375f) {
					qx2 = 3;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.0595703125f) {
					qx2 = 4;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.05810546875f) {
					qx2 = 5;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.05078125f) {
					qx2 = 6;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.04931640625f) {
					qx2 = 7;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.056640625f) {
					qx2 = 8;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.046875f) {
					qx2 = 9;
					qXnumbers.push_back(qx2);
				}
				else if (flattenedVertices[43] == 0.05517578125f) {
					qx2 = 0;
					qXnumbers.push_back(qx2);
				}
				else {
					//do nothing
				}
				//Third quad number
				if (flattenedVertices[63] == 0.04833984375f) {
					qx3 = 1;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.05224609375f) {
					qx3 = 2;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.0537109375f) {
					qx3 = 3;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.0595703125f) {
					qx3 = 4;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.05810546875f) {
					qx3 = 5;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.05078125f) {
					qx3 = 6;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.04931640625f) {
					qx3 = 7;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.056640625f) {
					qx3 = 8;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.046875f) {
					qx3 = 9;
					qXnumbers.push_back(qx3);
				}
				else if (flattenedVertices[63] == 0.05517578125f) {
					qx3 = 0;
					qXnumbers.push_back(qx3);
				}
				else {
					//do nothing
				}
				//Fourth quad number
				if (flattenedVertices[83] == 0.04833984375f) {
					qx4 = 1;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.05224609375f) {
					qx4 = 2;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.0537109375f) {
					qx4 = 3;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.0595703125f) {
					qx4 = 4;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.05810546875f) {
					qx4 = 5;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.05078125f) {
					qx4 = 6;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.04931640625f) {
					qx4 = 7;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.056640625f) {
					qx4 = 8;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.046875f) {
					qx4 = 9;
					qXnumbers.push_back(qx4);
				}
				else if (flattenedVertices[83] == 0.05517578125f) {
					qx4 = 0;
					qXnumbers.push_back(qx4);
				}
				else {
					//do nothing
				}
				//Fifth quad number
				if (flattenedVertices[103] == 0.04833984375f) {
					qx5 = 1;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.05224609375f) {
					qx5 = 2;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.0537109375f) {
					qx5 = 3;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.0595703125f) {
					qx5 = 4;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.05810546875f) {
					qx5 = 5;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.05078125f) {
					qx5 = 6;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.04931640625f) {
					qx5 = 7;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.056640625f) {
					qx5 = 8;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.046875f) {
					qx5 = 9;
					qXnumbers.push_back(qx5);
				}
				else if (flattenedVertices[103] == 0.05517578125f) {
					qx5 = 0;
					qXnumbers.push_back(qx5);
				}
				else {
					//do nothing
				}
				//GRID Y
				//First quad number
				if (flattenedVertices[163] == 0.04833984375f) {
					qy1 = 1;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.05224609375f) {
					qy1 = 2;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.0537109375f) {
					qy1 = 3;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.0595703125f) {
					qy1 = 4;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.05810546875f) {
					qy1 = 5;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.05078125f) {
					qy1 = 6;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.04931640625f) {
					qy1 = 7;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.056640625f) {
					qy1 = 8;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.046875f) {
					qy1 = 9;
					qYnumbers.push_back(qy1);
				}
				else if (flattenedVertices[163] == 0.05517578125f) {
					qy1 = 0;
					qYnumbers.push_back(qy1);
				}
				else {
					//do nothing
				}
				//Second quad number
				if (flattenedVertices[183] == 0.04833984375f) {
					qy2 = 1;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.05224609375f) {
					qy2 = 2;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.0537109375f) {
					qy2 = 3;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.0595703125f) {
					qy2 = 4;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.05810546875f) {
					qy2 = 5;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.05078125f) {
					qy2 = 6;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.04931640625f) {
					qy2 = 7;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.056640625f) {
					qx2 = 8;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.046875f) {
					qy2 = 9;
					qYnumbers.push_back(qy2);
				}
				else if (flattenedVertices[183] == 0.05517578125f) {
					qy2 = 0;
					qYnumbers.push_back(qy2);
				}
				else {
					//do nothing
				}
				//Third quad number
				if (flattenedVertices[203] == 0.04833984375f) {
					qy3 = 1;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.05224609375f) {
					qy3 = 2;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.0537109375f) {
					qy3 = 3;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.0595703125f) {
					qy3 = 4;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.05810546875f) {
					qy3 = 5;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.05078125f) {
					qy3 = 6;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.04931640625f) {
					qy3 = 7;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.056640625f) {
					qy3 = 8;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.046875f) {
					qy3 = 9;
					qYnumbers.push_back(qy3);
				}
				else if (flattenedVertices[203] == 0.05517578125f) {
					qy3 = 0;
					qYnumbers.push_back(qy3);
				}
				else {
					//do nothing
				}
				//Fourth quad number
				if (flattenedVertices[223] == 0.04833984375f) {
					qy4 = 1;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.05224609375f) {
					qy4 = 2;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.0537109375f) {
					qy4 = 3;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.0595703125f) {
					qy4 = 4;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.05810546875f) {
					qy4 = 5;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.05078125f) {
					qy4 = 6;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.04931640625f) {
					qy4 = 7;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.056640625f) {
					qy4 = 8;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.046875f) {
					qy4 = 9;
					qYnumbers.push_back(qy4);
				}
				else if (flattenedVertices[223] == 0.05517578125f) {
					qy4 = 0;
					qYnumbers.push_back(qy4);
				}
				else {
					//do nothing
				}
				//Fifth quad number
				if (flattenedVertices[243] == 0.04833984375f) {
					qy5 = 1;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.05224609375f) {
					qy5 = 2;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.0537109375f) {
					qy5 = 3;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.0595703125f) {
					qy5 = 4;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.05810546875f) {
					qy5 = 5;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.05078125f) {
					qy5 = 6;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.04931640625f) {
					qy5 = 7;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.056640625f) {
					qy5 = 8;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.046875f) {
					qy5 = 9;
					qYnumbers.push_back(qy5);
				}
				else if (flattenedVertices[243] == 0.05517578125f) {
					qy5 = 0;
					qYnumbers.push_back(qy5);
				}
				else {
					//do nothing
				}
				//=========================== COVERT ARRAY TO NUMBER!!! ========================
				for (int num : qXnumbers) {
					gridCellX = gridCellX * 10 + num;
				}
				for (int num : qYnumbers) {
					gridCellY = gridCellY * 10 + num;
				}
				shouldUpdateGrid = true;
				wasPressedLastFrame = true;
			}
			else if (!buttonIsPressed) {
				wasPressedLastFrame = false;
			}
		}
	}

	void createEditor() {
		createVertexArrays(1, editorVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, editorVBO, flattenedVertices.size() * sizeof(GLfloat), flattenedVertices.data(), GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0, 0);
		interpretData(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)), 1);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, editorEBO, flattenedIndices.size() * sizeof(GLint), flattenedIndices.data(), GL_STATIC_DRAW);

		unbindObjects(GL_VERTEX_ARRAY);
		unbindObjects(GL_ARRAY_BUFFER);
		unbindObjects(GL_ELEMENT_ARRAY_BUFFER);
	}

	void drawEditor() {
		glBindVertexArray(editorVAO);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(flattenedIndices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void activateAtlas(GLuint shaderProgram) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, editorTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureAtlasEditor"), 2);
	}
};