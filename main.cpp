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
#include "menu.h"

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
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Luigi's Engine", glfwGetPrimaryMonitor(), nullptr);
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
	//======================== MENU =====================
	Menu menuBox1, menuBox2, menuBox3;
	menuBox1.createMenu();
	menuBox2.createMenu();
	menuBox3.createMenu();
	//======================== MENU - Transformation matrices =================
	glm::mat4 menuBoxOne = glm::mat4(1.0f);
	GLuint menuBox1Location = glGetUniformLocation(shaderProgram, "transform");
	menuBox1.position = glm::vec3(1700.0f, 900.0f, 0.0f);
	menuBox1.width = 100;
	menuBox1.height = 25;

	glm::mat4 menuBoxTwo = glm::mat4(1.0f);
	GLuint menuBox2Location = glGetUniformLocation(shaderProgram, "transform");
	menuBox2.position = glm::vec3(1700.0f, 800.0f, 0.0f);
	menuBox2.width = 100;
	menuBox2.height = 25;

	glm::mat4 menuBoxThree = glm::mat4(1.0f);
	GLuint menuBox3Location = glGetUniformLocation(shaderProgram, "transform");
	menuBox3.position = glm::vec3(1700.0f, 700.0f, 0.0f);
	menuBox3.width = 100;
	menuBox3.height = 25;
	//======================== LEVEL I - ENVIRONMENT =====================
	Object floor, floorSquare;
	floor.createObject(ground, sizeof(ground) / sizeof(GLfloat), groundIndices, sizeof(groundIndices) / sizeof(int));
	floorSquare.createObject(groundSquare, sizeof(groundSquare) / sizeof(GLfloat), groundSquareIndices, sizeof(groundSquareIndices) / sizeof(int));
	//======================== LEVEL I - PLAYER ==============================================
	std::unique_ptr<Mage> mage = std::make_unique<Mage>();
	//Mage* mage = new Mage;
	mage->createMage(playerSquare, sizeof(playerSquare) / sizeof(GLfloat), playerSquareIndices, sizeof(playerSquareIndices) / sizeof(int));
	//======================== LEVEL I - Transformation matrices ==================================
	glm::mat4 staticFloor = glm::mat4(1.0f); // floor
	GLuint staticFloorLocation = glGetUniformLocation(shaderProgram, "transform");
	floor.position = glm::vec3(0.0f, 32.0f, 0.0f);
	floor.width = 9600;
	floor.height = 32;
	glm::mat4 playerMovement = glm::mat4(1.0f); // player
	GLuint playerMovementLocation = glGetUniformLocation(shaderProgram, "transform");
	mage->magePosition = glm::vec3(-8608.0f, 540.0f, 0.0f);
	mage->mageVelocity = glm::vec3(2000.0f, 2000.0f, 0.0f);
	//======================== LEVEL I - Camera ===================================================
	Camera camera;
	camera.createCamera();
	//======================= LEVEL I - Jumping ===================================================
	bool isJumping = false;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.8f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		float currentFrame = glfwGetTime(); //ignore the compiler warning about conversion from dbl to float and the possible loss of data
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		switch (gameState) {
		case gameMenu:
			glUseProgram(shaderProgram);
			camera.useCamera(shaderProgram);

			menuBoxOne = glm::mat4(1.0f);
			menuBoxOne = glm::translate(menuBoxOne, menuBox1.position);
			if (menuBox1.position.x - menuBox1.width < xpos && menuBox1.position.x + menuBox1.width > xpos && menuBox1.position.y - menuBox1.height < ypos
				&& menuBox1.position.y + menuBox1.height > ypos) {
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
					gameState = gameRunning;
				}
			}
			glUniformMatrix4fv(menuBox1Location, 1, GL_FALSE, glm::value_ptr(menuBoxOne));
			menuBox1.renderMenu();

			menuBoxTwo = glm::mat4(1.0f);
			menuBoxTwo = glm::translate(menuBoxTwo, menuBox2.position);
			if (menuBox2.position.x - menuBox2.width < xpos && menuBox2.position.x + menuBox2.width > xpos && menuBox2.position.y - menuBox2.height < ypos
				&& menuBox2.position.y + menuBox2.height > ypos) {
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
					gameState = gameOptions;
				}
			}
			glUniformMatrix4fv(menuBox2Location, 1, GL_FALSE, glm::value_ptr(menuBoxTwo));
			menuBox2.renderMenu();

			menuBoxThree = glm::mat4(1.0f);
			menuBoxThree = glm::translate(menuBoxThree, menuBox3.position);
			if (menuBox3.position.x - menuBox3.width < xpos && menuBox3.position.x + menuBox3.width > xpos && menuBox3.position.y - menuBox3.height < ypos
				&& menuBox3.position.y + menuBox3.height > ypos) {
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
					//more code in here to clean up resources please!!!
					glfwTerminate();
				}
			}
			glUniformMatrix4fv(menuBox3Location, 1, GL_FALSE, glm::value_ptr(menuBoxThree));
			menuBox3.renderMenu();

			break;
		case gameRunning:
			glUseProgram(shaderProgram);
			camera.updateView();
			camera.useCamera(shaderProgram);

			staticFloor = glm::mat4(1.0f);
			staticFloor = glm::translate(staticFloor, floor.position);
			glUniformMatrix4fv(staticFloorLocation, 1, GL_FALSE, glm::value_ptr(staticFloor));
			floor.drawObject();

			if (!isJumping && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				isJumping = true; // Start the jump
				mage->mageVelocity.y = 2500.0f; // Your initial jump velocity
			}

			playerMovement = glm::mat4(1.0f);
			playerMovement = glm::translate(playerMovement, mage->magePosition);
			mage->magePosition.y += mage->mageVelocity.y * deltaTime;
			if (mage->magePosition.y > 500.0f) {
				mage->mageVelocity.y = 0.0f;
			}
			if (mage->magePosition.y <= 146.0f && glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
				mage->mageVelocity.y = 0;
				isJumping = false;
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				mage->magePosition.x += mage->mageVelocity.x * deltaTime;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
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
			mage->magePosition.y -= 0.4f;

			mage->collisionMage(mage.get(), floor);
			break;

		case gameOptions:
			glUseProgram(shaderProgram);
			camera.useCamera(shaderProgram);
			break;
		}
		glfwSwapBuffers(window);
	}
	floor.cleanUp();
	mage->cleanUpMage();
	menuBox1.cleanUp();
	menuBox2.cleanUp();
	menuBox3.cleanUp();
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}