/*
 * camera.h
 *
 *  Created on: 20 de set. de 2015
 *      Author: starkus
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

struct Camera {
	GLfloat position[3];
	GLfloat orientation[3];

	void translateMatrix(); // TODO Remove this
	void rotateMatrix(); // TODO Remove this

	void viewMatrix(glm::mat4 &matrix);
};


#endif /* CAMERA_H */
