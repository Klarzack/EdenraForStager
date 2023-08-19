#pragma once

#include <GL/glew.h>
#include "utilities.h"
#include <glm/glm.hpp>
#include <vector>
#include "stb_image.h"
#include "mouse.h"

GLfloat editorQuad[]{
	-210.0f, 540.0f, 0.0f, 0.1008403361344538f, 0.0f,
	210.0f, 540.0f, 0.0f, 0.3361344537815126f, 0.0f,
	210.0f, -540.0f, 0.0f, 0.3361344537815126f, 0.8925619834710744f,
	-210.0f, -540.0f, 0.0f, 0.1008403361344538f, 0.8925619834710744f
};

GLint editorQuadIndices[]{
	0, 1, 2,
	0, 2, 3
};

GLfloat editorUserInput[]{
	-50.0f, 100.0f, 0.0f, 0.0f, 0.0f,
	50.0f, 100.0f, 0.0f, 1.0f, 0.0f,
	50.0f, -100.0f, 0.0f, 1.0f, 1.0f,
	-50.0f, -100.0f, 0.0f, 0.0f, 1.0f
};

GLint editorUserInputIndices[]{
	4, 5, 6,
	4, 6, 7
};

GLuint editorVAO{}, editorVBO{}, editorEBO{}, editorTexture{};

std::vector<float>verticesEditor{};
std::vector<int>indicesEditor{};

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
		//Editor Menu
		float v1{ editorQuad[0] }, v2{ editorQuad[1] }, v3{ editorQuad[2] }, v4{ editorQuad[3] }, v5{ editorQuad[4] },
			v6{ editorQuad[5] }, v7{ editorQuad[6] }, v8{ editorQuad[7] }, v9{ editorQuad[8] }, v10{ editorQuad[9] },
			v11{ editorQuad[10] }, v12{ editorQuad[11] }, v13{ editorQuad[12] }, v14{ editorQuad[13] }, v15{ editorQuad[14] },
			v16{ editorQuad[15] }, v17{ editorQuad[16] }, v18{ editorQuad[17] }, v19{ editorQuad[18] }, v20{ editorQuad[19] };
		int i1{ editorQuadIndices[0] }, i2{ editorQuadIndices[1] }, i3{ editorQuadIndices[2] }, i4{ editorQuadIndices[3] }, i5{ editorQuadIndices[4] },
			i6{ editorQuadIndices[5] };

		verticesEditor.push_back(v1);
		verticesEditor.push_back(v2);
		verticesEditor.push_back(v3);
		verticesEditor.push_back(v4);
		verticesEditor.push_back(v5);
		verticesEditor.push_back(v6);
		verticesEditor.push_back(v7);
		verticesEditor.push_back(v8);
		verticesEditor.push_back(v9);
		verticesEditor.push_back(v10);
		verticesEditor.push_back(v11);
		verticesEditor.push_back(v12);
		verticesEditor.push_back(v13);
		verticesEditor.push_back(v14);
		verticesEditor.push_back(v15);
		verticesEditor.push_back(v16);
		verticesEditor.push_back(v17);
		verticesEditor.push_back(v18);
		verticesEditor.push_back(v19);
		verticesEditor.push_back(v20);

		indicesEditor.push_back(i1);
		indicesEditor.push_back(i2);
		indicesEditor.push_back(i3);
		indicesEditor.push_back(i4);
		indicesEditor.push_back(i5);
		indicesEditor.push_back(i6);

		//text menu
		float v21{ editorUserInput[0] }, v22{ editorUserInput[1] }, v23{ editorUserInput[2] }, v24{ editorUserInput[3] }, v25{ editorUserInput[4] },
			v26{ editorUserInput[5] }, v27{ editorUserInput[6] }, v28{ editorUserInput[7] }, v29{ editorUserInput[8] }, v30{ editorUserInput[9] },
			v31{ editorUserInput[10] }, v32{ editorUserInput[11] }, v33{ editorUserInput[12] }, v34{ editorUserInput[13] }, v35{ editorUserInput[14] },
			v36{ editorUserInput[15] }, v37{ editorUserInput[16] }, v38{ editorUserInput[17] }, v39{ editorUserInput[18] }, v40{ editorUserInput[19] };
		int i7{ editorUserInputIndices[0] }, i8{ editorUserInputIndices[1] }, i9{ editorUserInputIndices[2] }, i10{ editorUserInputIndices[3] }, i11{ editorUserInputIndices[4] },
			i12{ editorUserInputIndices[5] };

		verticesEditor.push_back(v21);
		verticesEditor.push_back(v22);
		verticesEditor.push_back(v23);
		verticesEditor.push_back(v24);
		verticesEditor.push_back(v25);
		verticesEditor.push_back(v26);
		verticesEditor.push_back(v27);
		verticesEditor.push_back(v28);
		verticesEditor.push_back(v29);
		verticesEditor.push_back(v30);
		verticesEditor.push_back(v31);
		verticesEditor.push_back(v32);
		verticesEditor.push_back(v33);
		verticesEditor.push_back(v34);
		verticesEditor.push_back(v35);
		verticesEditor.push_back(v36);
		verticesEditor.push_back(v37);
		verticesEditor.push_back(v38);
		verticesEditor.push_back(v39);
		verticesEditor.push_back(v40);

		indicesEditor.push_back(i7);
		indicesEditor.push_back(i8);
		indicesEditor.push_back(i9);
		indicesEditor.push_back(i10);
		indicesEditor.push_back(i11);
		indicesEditor.push_back(i12);
	}	
	
	void createEditor() {
		createVertexArrays(1, editorVAO);
		createBufferObjects(GL_ARRAY_BUFFER, 1, editorVBO, 5 * verticesEditor.size() * sizeof(verticesEditor[0]), verticesEditor.data(), GL_STATIC_DRAW);
		interpretData(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0, 0);
		interpretData(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)), 1);
		createBufferObjects(GL_ELEMENT_ARRAY_BUFFER, 1, editorEBO, indicesEditor.size() * sizeof(int), indicesEditor.data(), GL_STATIC_DRAW);
	}

	void drawEditor() {
		glBindVertexArray(editorVAO);
		glDrawElements(GL_TRIANGLES, indicesEditor.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void activateAtlas(GLuint shaderProgram) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, editorTexture);
		glUniform1i(glGetUniformLocation(shaderProgram, "textureAtlasEditor"), 2);
	}
};