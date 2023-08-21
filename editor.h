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
bool q3textured = false;


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
		vertex.position[0] = glm::vec3(1500.0f, 1080.0f, 0.0f);
		vertex.position[1] = glm::vec3(1920.0f, 1080.0f, 0.0f);
		vertex.position[2] = glm::vec3(1920.0f, 0.0f, 0.0f);
		vertex.position[3] = glm::vec3(1500.0f, 0.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.0983606557377049f, 0.0f); //bottom left
		vertex.texture[1] = glm::vec2(0.3278688524590164f, 0.0f); // bottom right
		vertex.texture[2] = glm::vec2(0.3278688524590164f, 0.7912087912087912f); //top left
		vertex.texture[3] = glm::vec2(0.0983606557377049f, 0.7912087912087912f); //top right
		verticesEditor.push_back(vertex);
		//Text input 1	(1)
		vertex.position[0] = glm::vec3(1700.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1722.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1722.0f, 955.0f, 0.0f);
		vertex.position[3] = glm::vec3(1700.0f, 955.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.8852459016393443f, 0.3736263736263736f);
		vertex.texture[1] = glm::vec2(0.9289617486338798f, 0.3736263736263736f);
		vertex.texture[2] = glm::vec2(0.9289617486338798f, 0.4322344322344322f);
		vertex.texture[3] = glm::vec2(0.8852459016393443f, 0.4322344322344322f);
		verticesEditor.push_back(vertex);
		//Text input 2 (2)
		vertex.position[0] = glm::vec3(1724.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1746.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1746.0f, 955.0f, 0.0f);
		vertex.position[3] = glm::vec3(1724.0f, 955.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.8852459016393443f, 0.3736263736263736f);
		vertex.texture[1] = glm::vec2(0.9289617486338798f, 0.3736263736263736f);
		vertex.texture[2] = glm::vec2(0.9289617486338798f, 0.4322344322344322f);
		vertex.texture[3] = glm::vec2(0.8852459016393443f, 0.4322344322344322f);
		verticesEditor.push_back(vertex);
		//Text input 3	(3)
		vertex.position[0] = glm::vec3(1748.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1770.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1770.0f, 955.0f, 0.0f);
		vertex.position[3] = glm::vec3(1748.0f, 955.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.8852459016393443f, 0.3736263736263736f);
		vertex.texture[1] = glm::vec2(0.9289617486338798f, 0.3736263736263736f);
		vertex.texture[2] = glm::vec2(0.9289617486338798f, 0.4322344322344322f);
		vertex.texture[3] = glm::vec2(0.8852459016393443f, 0.4322344322344322f);
		verticesEditor.push_back(vertex);
		//Text input 4	(4)
		vertex.position[0] = glm::vec3(1772.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1794.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1794.0f, 955.0f, 0.0f);
		vertex.position[3] = glm::vec3(1772.0f, 955.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.8852459016393443f, 0.3736263736263736f);
		vertex.texture[1] = glm::vec2(0.9289617486338798f, 0.3736263736263736f);
		vertex.texture[2] = glm::vec2(0.9289617486338798f, 0.4322344322344322f);
		vertex.texture[3] = glm::vec2(0.8852459016393443f, 0.4322344322344322f);
		verticesEditor.push_back(vertex);
		//Text input 5 (5)
		vertex.position[0] = glm::vec3(1796.0f, 986.0f, 0.0f);
		vertex.position[1] = glm::vec3(1818.0f, 986.0f, 0.0f);
		vertex.position[2] = glm::vec3(1818.0f, 955.0f, 0.0f);
		vertex.position[3] = glm::vec3(1796.0f, 955.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.8852459016393443f, 0.3736263736263736f);
		vertex.texture[1] = glm::vec2(0.9289617486338798f, 0.3736263736263736f);
		vertex.texture[2] = glm::vec2(0.9289617486338798f, 0.4322344322344322f);
		vertex.texture[3] = glm::vec2(0.8852459016393443f, 0.4322344322344322f);
		verticesEditor.push_back(vertex);
		//Text input Container 6 (6)
		vertex.position[0] = glm::vec3(1690.0f, 988.0f, 0.0f);
		vertex.position[1] = glm::vec3(1828.0f, 988.0f, 0.0f);
		vertex.position[2] = glm::vec3(1828.0f, 957.0f, 0.0f);
		vertex.position[3] = glm::vec3(1690.0f, 957.0f, 0.0f);
		vertex.texture[0] = glm::vec2(0.0f, 0.8864468864468864f);
		vertex.texture[1] = glm::vec2(0.3770491803278689f, 0.8864468864468864f);
		vertex.texture[2] = glm::vec2(0.3770491803278689f, 1.0f);
		vertex.texture[3] = glm::vec2(0.0f, 1.0f);
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
		//Text Input Container 6
		index.indices[0] = 24; index.indices[1] = 25; index.indices[2] = 26;
		index.indices[3] = 24; index.indices[4] = 26; index.indices[5] = 27;
		indicesEditor.push_back(index);
		//PUSH THEM ALL TO THE VECTOR - FLATTENING INDICES
		for (auto& index : indicesEditor) {
			for (int i = 0; i < 6; i++) {
				flattenedIndices.push_back(index.indices[i]);
			}
		}
	}	
	
	void interactiveEditor(GLFWwindow* window) {
		if (xpos > 1700 && xpos < 1818 && ypos > 955 && ypos < 986) {
			if (keyPressed) {
				//verticesEditor.at(1).texture[0];
				flattenedVertices.at(23) = 0.5573770491803279;
				flattenedVertices.at(24) = 0.0f;
				//verticesEditor.at(1).texture[1];
				flattenedVertices.at(28) = 0.5655737704918033f;
				flattenedVertices.at(29) = 0.0f;
				//verticesEditor.at(1).texture[2];
				flattenedVertices.at(33) = 0.5655737704918033f;
				flattenedVertices.at(34) = 0.021978021978022f;
				//verticesEditor.at(1).texture[3];
				flattenedVertices.at(38) = 0.5573770491803279f;
				flattenedVertices.at(39) = 0.021978021978022f;
				//====================================================================================
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
			}
			else if (keyReleased) {
				q1textured = true;
			}
			if (keyPressed && q1textured) {
				//verticesEditor.at(1).texture[0];
				flattenedVertices.at(43) = 0.5573770491803279;
				flattenedVertices.at(44) = 0.0f;
				//verticesEditor.at(1).texture[1];
				flattenedVertices.at(48) = 0.5655737704918033f;
				flattenedVertices.at(49) = 0.0f;
				//verticesEditor.at(1).texture[2];
				flattenedVertices.at(53) = 0.5655737704918033f;
				flattenedVertices.at(54) = 0.021978021978022f;
				//verticesEditor.at(1).texture[3];
				flattenedVertices.at(58) = 0.5573770491803279f;
				flattenedVertices.at(59) = 0.021978021978022f;
				//====================================================================================
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
			}
			else if (keyReleased && q1textured) {
				q2textured = true;
			}
			if (keyPressed && q2textured) {
				//verticesEditor.at(1).texture[0];
				flattenedVertices.at(63) = 0.5573770491803279;
				flattenedVertices.at(64) = 0.0f;
				//verticesEditor.at(1).texture[1];
				flattenedVertices.at(68) = 0.5655737704918033f;
				flattenedVertices.at(69) = 0.0f;
				//verticesEditor.at(1).texture[2];
				flattenedVertices.at(73) = 0.5655737704918033f;
				flattenedVertices.at(74) = 0.021978021978022f;
				//verticesEditor.at(1).texture[3];
				flattenedVertices.at(78) = 0.5573770491803279f;
				flattenedVertices.at(79) = 0.021978021978022f;
				//====================================================================================
				glBindBuffer(GL_ARRAY_BUFFER, editorVBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * flattenedVertices.size(), flattenedVertices.data());
				glBindVertexArray(editorVAO);
			}
			else if (keyReleased && q2textured) {
				q3textured = true;
			}
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