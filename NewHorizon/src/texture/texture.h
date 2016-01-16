/*
 * texture.h
 *
 *  Created on: 8 de ene. de 2016
 *      Author: starkus
 */

#ifndef TEXTURE_TEXTURE_H_
#define TEXTURE_TEXTURE_H_


#include <GL/glew.h>
#include <string>
#include "../util/png.h"


#define NULL_TEXTURE	((GLuint) -1)


struct texture {
	GLuint id;
	int width, height;
	std::string name;

	texture(const char* filename);
};

void removeLocation(const char* filename, char* target);


#endif /* TEXTURE_TEXTURE_H_ */
