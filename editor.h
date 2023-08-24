#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <glm/glm.hpp>
#include <vector>
#include "stb_image.h"
#include "mouse.h"
#include "keyboard.h"

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
bool q2textured = false;
bool allowq2release = false;
bool q3textured = false;
bool allowq3release = false;
bool q4textured = false;
bool allowq4release = false;
bool q5textured = false;
bool allowq5release = false;
bool activateTextInput = false;

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
		//Text input 1	(1)
		vertex.position[0] = glm::vec3(1700.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1716.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1716.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1700.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible   //23, 24
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible  //28, 29 ... etc.
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 2 (2)
		vertex.position[0] = glm::vec3(1718.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1734.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1734.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1718.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 3	(3)
		vertex.position[0] = glm::vec3(1736.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1752.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1752.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1736.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 4	(4)
		vertex.position[0] = glm::vec3(1754.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1770.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1770.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1754.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Text input 5 (5)
		vertex.position[0] = glm::vec3(1772.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1788.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1788.0f, 958.0f, 0.0f);
		vertex.position[3] = glm::vec3(1772.0f, 958.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Selector for text input right (6)
		vertex.position[0] = glm::vec3(1890.0f, 995.0f, 0.0f);
		vertex.position[1] = glm::vec3(1905.0f, 995.0f, 0.0f);
		vertex.position[2] = glm::vec3(1905.0f, 950.0f, 0.0f);
		vertex.position[3] = glm::vec3(1890.0f, 950.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.99951171875f, 0.99951171875f); //made invisible
		vertex.texture[1] = glm::vec2(1.0f, 0.99951171875f);//made invisible
		vertex.texture[2] = glm::vec2(1.0f, 1.0f);//made invisible
		vertex.texture[3] = glm::vec2(0.99951171875f, 1.0f);//made invisible
		verticesEditor.push_back(vertex);
		//Selector for text input left (6)
		vertex.position[0] = glm::vec3(1515.125f, 995.0f, 0.0f);
		vertex.position[1] = glm::vec3(1530.0f, 995.0f, 0.0f);
		vertex.position[2] = glm::vec3(1530.0f, 950.0f, 0.0f);
		vertex.position[3] = glm::vec3(1515.125f, 950.0f, 0.0f);
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
		//Text Input 1
		index.indices[0] = 4; index.indices[1] = 5; index.indices[2] = 6;
		index.indices[3] = 4; index.indices[4] = 6; index.indices[5] = 7;
		indicesEditor.push_back(index);
		//Text Input 2
		index.indices[0] = 8; index.indices[1] = 9; index.indices[2] = 10;
		index.indices[3] = 8; index.indices[4] = 10; index.indices[5] = 11;
		indicesEditor.push_back(index);
		//Text Input 3
		index.indices[0] = 12; index.indices[1] = 13; index.indices[2] = 14;
		index.indices[3] = 12; index.indices[4] = 14; index.indices[5] = 15;
		indicesEditor.push_back(index);
		//Text Input 4
		index.indices[0] = 16; index.indices[1] = 17; index.indices[2] = 18;
		index.indices[3] = 16; index.indices[4] = 18; index.indices[5] = 19;
		indicesEditor.push_back(index);
		//Text Input 5
		index.indices[0] = 20; index.indices[1] = 21; index.indices[2] = 22;
		index.indices[3] = 20; index.indices[4] = 22; index.indices[5] = 23;
		indicesEditor.push_back(index);
		//Selector for text input right
		index.indices[0] = 24; index.indices[1] = 25; index.indices[2] = 26;
		index.indices[3] = 24; index.indices[4] = 26; index.indices[5] = 27;
		indicesEditor.push_back(index);
		//Selector for text input left
		index.indices[0] = 28; index.indices[1] = 29; index.indices[2] = 30;
		index.indices[3] = 28; index.indices[4] = 30; index.indices[5] = 31;
		indicesEditor.push_back(index);
		//PUSH THEM ALL TO THE VECTOR - FLATTENING INDICES
		for (auto& index : indicesEditor) {
			for (int i = 0; i < 6; i++) {
				flattenedIndices.push_back(index.indices[i]);
			}
		}
	}	
	
	void interactiveEditor(GLFWwindow* window) {

		if (xpos > 1667.0f && xpos < 1884.0f && ypos > 956.0f && ypos < 990.0f) {
			buttonIsInRangeGridSizeX = true;
		}
		else {
			buttonIsInRangeGridSizeX = false;
		}
		if (buttonIsInRangeGridSizeX) {
			if (buttonIsPressed) {
				activateTextInput = true;
			}
		}
		if (!buttonIsInRangeGridSizeX) {
			if (buttonIsPressed) {
				activateTextInput = false;
			}
		}
		if (activateTextInput) {
			flattenedVertices.at(123) = 0.046875f;   //top left
			flattenedVertices.at(124) = 0.01123046875f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(128) = 0.04833984375f;    //top right
			flattenedVertices.at(129) = 0.01123046875f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(133) = 0.04833984375f;    //bottom right
			flattenedVertices.at(134) = 0.013671875f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(138) = 0.046875;   //bottom left
			flattenedVertices.at(139) = 0.013671875f;

			flattenedVertices.at(143) = 0.046875f;   //top left
			flattenedVertices.at(144) = 0.01123046875f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(148) = 0.04833984375f;    //top right
			flattenedVertices.at(149) = 0.01123046875f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(153) = 0.04833984375f;    //bottom right
			flattenedVertices.at(154) = 0.013671875f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(158) = 0.046875;   //bottom left
			flattenedVertices.at(159) = 0.013671875f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);

		//Quad1
		if (key1Pressed && !q1textured) {
			//verticesEditor.at(1).texture[0];
			flattenedVertices.at(23) = 0.04833984375f;   //top left
			flattenedVertices.at(24) = 0.0f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(28) = 0.04931640625f;    //top right
			flattenedVertices.at(29) = 0.0f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(33) = 0.04931640625f;    //bottom right
			flattenedVertices.at(34) = 0.00244140625f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(38) = 0.04833984375f;   //bottom left
			flattenedVertices.at(39) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			keyBackspaceReleased = false;
		}
		else if (key2Pressed && !q1textured) {
			//verticesEditor.at(1).texture[0];
			flattenedVertices.at(23) = 0.05224609375f;   //top left
			flattenedVertices.at(24) = 0.0f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(28) = 0.0537109375f;    //top right
			flattenedVertices.at(29) = 0.0f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(33) = 0.0537109375f;    //bottom right
			flattenedVertices.at(34) = 0.00244140625f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(38) = 0.05224609375f;   //bottom left
			flattenedVertices.at(39) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			keyBackspaceReleased = false;
		}
		else if (key1Released || key2Released) {
			q1textured = true;
		}
		//Quad 1 delete method
		if (keyBackspacePressed && q1textured && !q2textured) {
			flattenedVertices.at(23) = 0.99951171875f;   
			flattenedVertices.at(24) = 0.99951171875f;
			flattenedVertices.at(28) = 1.0f;  
			flattenedVertices.at(29) = 0.99951171875f;
			flattenedVertices.at(33) = 1.0f;    
			flattenedVertices.at(34) = 1.0f;
			flattenedVertices.at(38) = 0.99951171875f;   
			flattenedVertices.at(39) = 1.0;
		}
		else if (keyBackspaceReleased && flattenedVertices.at(23) == 0.99951171875f) {
			q1textured = false;
		}
		//Quad2
		if (key1Pressed && q1textured && !q2textured) {

			flattenedVertices.at(43) = 0.04833984375f;   //top left
			flattenedVertices.at(44) = 0.0f;

			flattenedVertices.at(48) = 0.04931640625f;    //top right
			flattenedVertices.at(49) = 0.0f;

			flattenedVertices.at(53) = 0.04931640625f;    //bottom right
			flattenedVertices.at(54) = 0.00244140625f;

			flattenedVertices.at(58) = 0.04833984375f;   //bottom left
			flattenedVertices.at(59) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq2release = true;
			keyBackspaceReleased = false;
		}
		else if (key2Pressed && q1textured && !q2textured) {
			//verticesEditor.at(1).texture[0];
			flattenedVertices.at(43) = 0.05224609375f;   //top left
			flattenedVertices.at(44) = 0.0f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(48) = 0.0537109375f;    //top right
			flattenedVertices.at(49) = 0.0f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(53) = 0.0537109375f;    //bottom right
			flattenedVertices.at(54) = 0.00244140625f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(58) = 0.05224609375f;   //bottom left
			flattenedVertices.at(59) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq2release = true;
			keyBackspaceReleased = false;
		}
		else if ((key1Released && q1textured && allowq2release) || (key2Released && q1textured && allowq2release)) {
			q2textured = true;
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
		else if (keyBackspaceReleased && flattenedVertices.at(43) == 0.99951171875f) {
			q2textured = false;
			allowq2release = false;
		}
		//Quad3
		if (key1Pressed && q2textured && !q3textured) {

			flattenedVertices.at(63) = 0.04833984375f;   //top left
			flattenedVertices.at(64) = 0.0f;

			flattenedVertices.at(68) = 0.04931640625f;    //top right
			flattenedVertices.at(69) = 0.0f;

			flattenedVertices.at(73) = 0.04931640625f;    //bottom right
			flattenedVertices.at(74) = 0.00244140625f;

			flattenedVertices.at(78) = 0.04833984375f;   //bottom left
			flattenedVertices.at(79) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq3release = true;
			keyBackspaceReleased = false;
		}
		else if (key2Pressed && q2textured && !q3textured) {
			//verticesEditor.at(1).texture[0];
			flattenedVertices.at(63) = 0.05224609375f;   //top left
			flattenedVertices.at(64) = 0.0f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(68) = 0.0537109375f;    //top right
			flattenedVertices.at(69) = 0.0f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(73) = 0.0537109375f;    //bottom right
			flattenedVertices.at(74) = 0.00244140625f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(78) = 0.05224609375f;   //bottom left
			flattenedVertices.at(79) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq3release = true;
			keyBackspaceReleased = false;
		}
		else if ((key1Released && q2textured && allowq3release) || (key2Released && q2textured && allowq3release)) {
			q3textured = true;
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
		else if (keyBackspaceReleased && flattenedVertices.at(63) == 0.99951171875f) {
			q3textured = false;
			allowq3release = false;
		}
		//Quad4
		if (key1Pressed && q3textured && !q4textured) {

			flattenedVertices.at(83) = 0.04833984375f;   //top left
			flattenedVertices.at(84) = 0.0f;

			flattenedVertices.at(88) = 0.04931640625f;    //top right
			flattenedVertices.at(89) = 0.0f;

			flattenedVertices.at(93) = 0.04931640625f;    //bottom right
			flattenedVertices.at(94) = 0.00244140625f;

			flattenedVertices.at(98) = 0.04833984375f;   //bottom left
			flattenedVertices.at(99) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq4release = true;
		}
		else if (key2Pressed && q3textured && !q4textured) {
			//verticesEditor.at(1).texture[0];
			flattenedVertices.at(83) = 0.05224609375f;   //top left
			flattenedVertices.at(84) = 0.0f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(88) = 0.0537109375f;    //top right
			flattenedVertices.at(89) = 0.0f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(93) = 0.0537109375f;    //bottom right
			flattenedVertices.at(94) = 0.00244140625f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(98) = 0.05224609375f;   //bottom left
			flattenedVertices.at(99) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq4release = true;
			keyBackspaceReleased = false;
		}
		else if ((key1Released && q3textured && allowq4release) || (key2Released && q3textured && allowq4release)) {
			q4textured = true;
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
		else if (keyBackspaceReleased && flattenedVertices.at(83) == 0.99951171875f) {
			q4textured = false;
			allowq4release = false;
		}
		//Quad5
		if (key1Pressed && q4textured && !q5textured) {

			flattenedVertices.at(103) = 0.04833984375f;   //top left
			flattenedVertices.at(104) = 0.0f;

			flattenedVertices.at(108) = 0.04931640625f;    //top right
			flattenedVertices.at(109) = 0.0f;

			flattenedVertices.at(113) = 0.04931640625f;    //bottom right
			flattenedVertices.at(114) = 0.00244140625f;

			flattenedVertices.at(118) = 0.04833984375f;   //bottom left
			flattenedVertices.at(119) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq5release = true;
		}
		else if (key2Pressed && q4textured && !q5textured) {
			//verticesEditor.at(1).texture[0];
			flattenedVertices.at(103) = 0.05224609375f;   //top left
			flattenedVertices.at(104) = 0.0f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(108) = 0.0537109375f;    //top right
			flattenedVertices.at(109) = 0.0f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(113) = 0.0537109375f;    //bottom right
			flattenedVertices.at(114) = 0.00244140625f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(118) = 0.05224609375f;   //bottom left
			flattenedVertices.at(119) = 0.00244140625f;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
			allowq5release = true;
			keyBackspaceReleased = false;
		}
		else if ((key1Released && q3textured && allowq5release) || (key2Released && q3textured && allowq5release)) {
			q5textured = true;
		}
		//Quad 5 delete method
		if (keyBackspacePressed && q5textured) {
			flattenedVertices.at(103) = 0.99951171875f;
			flattenedVertices.at(104) = 0.99951171875f;
			flattenedVertices.at(108) = 1.0f;
			flattenedVertices.at(109) = 0.99951171875f;
			flattenedVertices.at(113) = 1.0f;
			flattenedVertices.at(114) = 1.0f;
			flattenedVertices.at(118) = 0.99951171875f;
			flattenedVertices.at(119) = 1.0;
		}
		else if (keyBackspaceReleased && flattenedVertices.at(103) == 0.99951171875f) {
			q5textured = false;
			allowq5release = false;
		}
		}
		else {
			flattenedVertices.at(123) = 0.99951171875f;   //top left
			flattenedVertices.at(124) = 0.99951171875f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(128) = 1.0f;    //top right
			flattenedVertices.at(129) = 0.99951171875f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(133) = 1.0f;    //bottom right
			flattenedVertices.at(134) = 1.0f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(138) = 0.99951171875f;   //bottom left
			flattenedVertices.at(139) = 1.0;

			flattenedVertices.at(143) = 0.99951171875f;   //top left
			flattenedVertices.at(144) = 0.99951171875f;
			//verticesEditor.at(1).texture[1];
			flattenedVertices.at(148) = 1.0f;    //top right
			flattenedVertices.at(149) = 0.99951171875f;
			//verticesEditor.at(1).texture[2];
			flattenedVertices.at(153) = 1.0f;    //bottom right
			flattenedVertices.at(154) = 1.0f;
			//verticesEditor.at(1).texture[3];
			flattenedVertices.at(158) = 0.99951171875f;   //bottom left
			flattenedVertices.at(159) = 1.0;
			//====================================================================================
			glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)* flattenedVertices.size(), flattenedVertices.data());
			glBindVertexArray(editorVAO);
		}
	}

	void createEditor() {
		createVertexArrays(1, editorVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, editorVBO, flattenedVertices.size() * sizeof(GLfloat), flattenedVertices.data(), GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0, 0);
		interpretData(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)), 1);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, editorEBO, flattenedIndices.size() * sizeof(GLint), flattenedIndices.data(), GL_STATIC_DRAW);
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