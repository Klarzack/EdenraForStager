#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utilities.h"
#include "mouse.h"
#include "gameState.h"
#include "camera.h"
#include "grid.h"
#include "menu.h"
#include "editor.h"
#include "keyboard.h"
#include <cmath>
#include "gridLines.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int screenWidth{ 1920 };
const int screenHeight{ 1080 };

float xpos{}, ypos{};

int main() {

	if (!glfwInit()) {
		std::cerr << "GLFW failed to initialize" << std::endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Edenra Engine", glfwGetPrimaryMonitor(), nullptr);
	if (!window) {
		std::cerr << "GLFW failed to create a window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);

	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return 1;
	}
	//============== enable alpha blending for png images =============
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//================ Read shaders from file ==========================
	std::string vShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/vertexShader.vert");
	const GLchar* vs = vShader.c_str();
	std::string fShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/fragmentShader.frag");
	const GLchar* fs = fShader.c_str();
	GLuint shaderProgram = createShaderProgram(vs, fs);
	vShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/vertexShaderMenu.vert");
	vs = vShader.c_str();
	fShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/fragmentShaderMenu.frag");
	fs = fShader.c_str();
	GLuint shaderProgramMenu = createShaderProgram(vs, fs);
	vShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/vertexShaderEditor.vert");
	vs = vShader.c_str();
	fShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/fragmentShaderEditor.frag");
	fs = fShader.c_str();
	GLuint shaderProgramEditor = createShaderProgram(vs, fs);
	vShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/vertexShaderGridLines.vert");
	vs = vShader.c_str();
	fShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/fragmentShaderGridLines.frag");
	fs = fShader.c_str();
	GLuint shaderProgramLines = createShaderProgram(vs, fs);
	//================================= Round up =========================
	auto roundUp = [](double value) -> int {
		return (value - static_cast<int>(value) >= 0.5) ? static_cast<int>(ceil(value)) : static_cast<int>(value);
	};
	//================================ Screen Origin/Center ==============
	glm::vec3 screenCenter(960.0f, 540.0f, 0.0f);
	//================================ Custom Cursor =====================
	CustomCursor cursorX;
	cursorX.loadImage(window);
	//===================== Delta Time =================================
	double deltaTime = 0.0;
	double lastFrame = 0.0;
	//======================== Camera ==================================
	Camera camera;
	camera.createCamera();
	//======================= Menu =====================================
	Menu menu;
	menu.loadTexture();
	menu.populateMenu();
	menu.createMenu();
	bool isMenuAtlasActivated = false;
	//======================= Grid =================================
	Grid grid;
	grid.loadTexture();
	grid.createGrid();
	//====================== Editor ================================
	Editor editor;
	editor.loadTexture();
	editor.populateEditor();
	editor.createEditor();
	bool isEditorAtlasActivated = false;
	//===================== Grid Lines =============================
	GridLines lines;
	lines.createGridLines();
	bool frustumOff = false;

	while (!glfwWindowShouldClose(window))
	{	
		glUseProgram(shaderProgram);
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		switch (gameState) {

		case gameMenu: {
			glUseProgram(shaderProgramMenu);
			camera.useCamera(shaderProgramMenu);
			if (camera.cameraPosition.x != 0.0f && camera.cameraPosition.y != 0.0f) {
				camera.cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
			}
			camera.updateView();

			glm::mat4 menuMatrix = glm::mat4(1.0f);
			GLuint menuMatrixLocation = glGetUniformLocation(shaderProgramMenu, "transform");
			glUniformMatrix4fv(menuMatrixLocation, 1, GL_FALSE, glm::value_ptr(menuMatrix));
			if (!isMenuAtlasActivated) {
				menu.activateAtlas(shaderProgramMenu);
				isMenuAtlasActivated = true;
			}
			menu.drawMenu();
			menu.interactiveMenu(window);
			break;
		}

		case gameEditor: {

			glUseProgram(shaderProgram);
			camera.useCamera(shaderProgram);
			camera.freeCamera(screenCenter, deltaTime, xpos, ypos);
			camera.updateView();
			glm::mat4 gridMatrix = glm::mat4(1.0f);
			GLuint gridMatrixLocation = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(gridMatrixLocation, 1, GL_FALSE, glm::value_ptr(gridMatrix));
			if (shouldUpdateGrid) {
				grid.deleteGrid();
				grid.activateAtlas(shaderProgram);
				grid.populateGrid(roundUp(gridCellY / 64.0), roundUp(gridCellX / 64.0));
				grid.createGrid();
				shouldUpdateGrid = false;
			}
			if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
				frustumOff = true;
			}
			else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
				frustumOff = false;
			}
			if (!frustumOff) {
				camera.activateFrustumCulling();
			}
			grid.drawGrid();

			if (isGridLinesToggled) {
				glUseProgram(shaderProgramLines);
				camera.useCamera(shaderProgramLines);
				glm::mat4 linesMatrix = glm::mat4(1.0f);
				GLuint linesMatrixLocation = glGetUniformLocation(shaderProgramLines, "transform");
				glUniformMatrix4fv(linesMatrixLocation, 1, GL_FALSE, glm::value_ptr(linesMatrix));
				if (shouldUpdateLines) {
					lines.deleteGridLines();
					lines.populateGridLines((roundUp(gridCellY / 64.0)) + 1, (roundUp(gridCellX / 64.0)) + 1); // +1 to the first parameter always, +2 to the second. ALWAYS!!!!!!!!!!!!!
					lines.createGridLines();
					shouldUpdateLines = false;
				}
				lines.drawGridLines(shaderProgramLines);
			}

			glUseProgram(shaderProgramEditor);
			camera.useCamera(shaderProgramEditor);
			glm::mat4 editorMatrix = glm::translate(glm::mat4(1.0f), camera.cameraPosition);
			GLuint editorMatrixLocation = glGetUniformLocation(shaderProgramEditor, "transform");
			glUniformMatrix4fv(editorMatrixLocation, 1, GL_FALSE, glm::value_ptr(editorMatrix));
			if (!isEditorAtlasActivated) {
				editor.activateAtlas(shaderProgramEditor);
				isEditorAtlasActivated = true;
			}
			editor.drawEditor();
			editor.interactiveEditor(window);
			editor.assignValuesGrid();

			break;
		}

		}

		glfwSwapBuffers(window);
	}

	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgramMenu);
	glDeleteProgram(shaderProgramEditor);
	glDeleteProgram(shaderProgramLines);


	glfwTerminate();
	return 0;
}