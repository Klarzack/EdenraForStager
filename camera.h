#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Camera {

	float width{ 1920 };
	float height{ 1080 };
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);

   void updateView() {
	   view = glm::translate(glm::mat4(1.0f), -cameraPosition);
   }

   void createCamera() {
	   projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
   }

   void useCamera(GLuint shaderProgram) {
	   GLuint viewLocation = glGetUniformLocation(shaderProgram, "view");
	   glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	   GLuint projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	   glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
   }

   //move camera around
   void freeCamera(glm::vec3& screenCenter, double deltaTime, float xpos, float ypos) {
	   if (xpos > screenCenter.x + 958.0f) {
		   cameraPosition.x += 500.0f * deltaTime;
	   }
	   else if (xpos < screenCenter.x - 958.0f) {
		   cameraPosition.x -= 500.0f * deltaTime;
	   }

	   if (ypos > screenCenter.y + 538.0f) {
		   cameraPosition.y += 500.0f * deltaTime;
	   }
	   else if (ypos < screenCenter.y - 538.0f) {
		   cameraPosition.y -= 500.0f * deltaTime;
	   }
	}
};