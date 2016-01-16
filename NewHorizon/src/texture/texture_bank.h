/*
 * texture_bank.h
 *
 *  Created on: 8 de ene. de 2016
 *      Author: starkus
 */

#ifndef UTIL_TEXTURE_BANK_H_
#define UTIL_TEXTURE_BANK_H_


#include <map>
#include <string>
#include <GL/glew.h>
#include "texture.h"


static std::map<std::string, texture> _textures;

GLuint findOrReg(char* filename);


#endif /* UTIL_TEXTURE_BANK_H_ */
