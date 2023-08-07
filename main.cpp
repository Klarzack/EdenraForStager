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
#include "deadPass.h"
#include "camera.h"
#include "entities.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int screenWidth{ 1920 };
const int screenHeight{ 1080 };

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

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Luigi's Engine", nullptr, nullptr);
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

	//================ Read shaders from file ===========================================
	std::string vShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/vertexShader.vert");
	const GLchar* vs = vShader.c_str();
	std::string fShader = loadShaderSource("C:/Users/istra/Edenra/Edenra/fragmentShader.frag");
	const GLchar* fs = fShader.c_str();
	GLuint shaderProgram = createShaderProgram(vs, fs);
	//===================== Delta Time ============================
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	//======================== ALL THE OBJECTS I NEED FOR CHAPTER I =====================
	Object floor, floorSquare;
	floor.createObject(ground, sizeof(ground) / sizeof(GLfloat), groundIndices, sizeof(groundIndices) / sizeof(int));
	floorSquare.createObject(groundSquare, sizeof(groundSquare) / sizeof(GLfloat), groundSquareIndices, sizeof(groundSquareIndices) / sizeof(int));
	//======================== Player Mage ==============================================
	std::unique_ptr<Mage> mage = std::make_unique<Mage>();
	//Mage* mage = new Mage;
	mage->createMage(playerSquare, sizeof(playerSquare) / sizeof(GLfloat), playerSquareIndices, sizeof(playerSquareIndices) / sizeof(int));
	//======================== Transformation matrices ==================================
	glm::mat4 staticFloor = glm::mat4(1.0f); // floor
	GLuint staticFloorLocation = glGetUniformLocation(shaderProgram, "transform");
	floor.position = glm::vec3(0.0f, 50.0f, 0.0f);
	floor.width = 9600;
	floor.height = 32;
	glm::mat4 playerMovement = glm::mat4(1.0f); // player
	GLuint playerMovementLocation = glGetUniformLocation(shaderProgram, "transform");
	mage->magePosition = glm::vec3(960.0f, 540.0f, 0.0f);
	mage->mageVelocity = glm::vec3(2000.0f, 4000.0f, 0.0f);
	//======================== Camera ===================================================
	Camera camera;
	camera.createCamera();
	//===================================================================================
	std::cout << floor.position.y;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		camera.updateView();
		camera.useCamera(shaderProgram);

		staticFloor = glm::mat4(1.0f);
		staticFloor = glm::translate(staticFloor, floor.position);
		glUniformMatrix4fv(staticFloorLocation, 1, GL_FALSE, glm::value_ptr(staticFloor));
		floor.drawObject();

		playerMovement = glm::mat4(1.0f);
		playerMovement = glm::translate(playerMovement, mage->magePosition);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			mage->magePosition.y += mage->mageVelocity.y * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			mage->magePosition.x += mage->mageVelocity.x * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			mage->magePosition.x -= mage->mageVelocity.x * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			std::cout << "Position X: " << mage->magePosition.x;
		}
		glUniformMatrix4fv(playerMovementLocation, 1, GL_FALSE, glm::value_ptr(playerMovement));
		mage->drawMage();
		
		//follow player
		camera.cameraPosition.x = mage->magePosition.x - 960.0f;
		if (mage->magePosition.y > 540.0f) {
			camera.cameraPosition.y = mage->magePosition.y - 540.0f;
		}
		//gravity, ACTIVATE IT WHEN NEEDED
		mage->magePosition.y -= 1.0f;

		mage->collisionMage(mage.get(), floor);
		
		glfwSwapBuffers(window);
	}
	floor.cleanUp();
	mage->cleanUpMage();
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}