/*
 * png.h
 *
 *  Created on: 28 de oct. de 2015
 *      Author: starkus
 */

#ifndef UTIL_PNG_H_
#define UTIL_PNG_H_


#include <png.h>
#include <stdlib.h>
#include <GL/glew.h>


GLuint PNG_load(const char* filename, int* width, int* height);


#endif /* UTIL_PNG_H_ */
