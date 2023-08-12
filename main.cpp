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
	// Use glfwGetPrimaryMonitor() as a 4th parameter of glfwCreateWindow instead of the first NULL to create a full screen mode
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Edenra Engine", glfwGetPrimaryMonitor(), nullptr);
	if (!window) {
		std::cerr << "GLFW failed to create a window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);

	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return 1;
	}
	//================ Read shaders from file ==========================
	std::string vShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/vertexShader.vert");
	const GLchar* vs = vShader.c_str();
	std::string fShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/fragmentShader.frag");
	const GLchar* fs = fShader.c_str();
	GLuint shaderProgram = createShaderProgram(vs, fs);
	//===================== Delta Time =================================
	double deltaTime = 0.0;
	double lastFrame = 0.0;
	//======================== Camera ==================================
	Camera camera;
	camera.createCamera();
	//==================================================================
	Grid grid;
	grid.populateGrid(50);
	grid.createGrid();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glUseProgram(shaderProgram);
		camera.useCamera(shaderProgram);

		glm::mat4 gridMatrix = glm::mat4(1.0f);
		//gridMatrix = glm::translate(gridMatrix, glm::vec3(960.0f, 540.0f, 0.0f));
		GLuint gridMatrixLocation = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(gridMatrixLocation, 1, GL_FALSE, glm::value_ptr(gridMatrix));
		grid.drawGrid();

		glfwSwapBuffers(window);
	}

	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}