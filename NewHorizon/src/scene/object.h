/*
 * object.h
 *
 *  Created on: 26 de set. de 2015
 *      Author: starkus
 */

#ifndef SCENE_OBJECT_H_
#define SCENE_OBJECT_H_


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "../geometry/vbo.hpp"
#include "../geometry/mesh.h"



class Object {
private:
	char *name;
	VBO *vbo;

public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Object(char *name, VBO *vbo);

	void setModel(VBO *model) {
		vbo = model;
	}

	void draw(GLuint program, glm::mat4 projview, GLuint modelID);
};


#endif /* SCENE_OBJECT_H_ */
