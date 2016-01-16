/*
 * camera.cpp
 *
 *  Created on: 20 de set. de 2015
 *      Author: starkus
 */

#include <GL/gl.h>

#include "camera.h"


void Camera::translateMatrix() {
	glTranslatef(-position[0], -position[1], -position[2]);
}

void Camera::rotateMatrix() {
	glRotatef(-orientation[0], 1.0, 0.0, 0.0);
	glRotatef(-orientation[1], 0.0, 1.0, 0.0);
	glRotatef(-orientation[2], 0.0, 0.0, 1.0);
}

void Camera::viewMatrix(glm::mat4 &matrix) {
	matrix = glm::lookAt(
				glm::vec3(0, 0, position[2]),
				glm::vec3(0, 0, 0),
				glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix,  orientation[0], glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, -orientation[2], glm::vec3(0, 0, 1));
}

