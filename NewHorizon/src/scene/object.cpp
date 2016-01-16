/*
 * object.cpp
 *
 *  Created on: 26 de set. de 2015
 *      Author: starkus
 */


#include "object.h"

using namespace glm;


#define RADIANS(i) i * 2 * 3.1415 / 360.0


Object::Object(char *name, VBO *vbo) {
	this->name = name;
	this->vbo = vbo;
	scale = vec3(1);
	rotation = vec3(0, 0, 0);
}

void Object::draw(GLuint program, glm::mat4 projview, GLuint modelID) {
	mat4 model(1);

	model = rotate(model, rotation[0], glm::vec3(1, 0, 0));
	model = rotate(model, rotation[1], glm::vec3(0, 1, 0));
	model = rotate(model, rotation[2], glm::vec3(0, 0, 1));

	model *= mat4(
			vec4(1, 0, 0, 0),
			vec4(0, 1, 0, 0),
			vec4(0, 0, 1, 0),
			vec4(position[0], position[1], position[2], 1));

	model *= mat4(
			vec4(scale[0], 0, 0, 0),
			vec4(0, scale[1], 0, 0),
			vec4(0, 0, scale[2], 0),
			vec4(0, 0, 0, 1));

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	vbo->draw(program);
}
