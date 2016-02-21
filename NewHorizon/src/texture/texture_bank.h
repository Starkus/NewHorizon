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


typedef std::map<std::string, texture> texmap;
//static texmap _textures;

//GLuint findOrReg(char* filename);


class TextureBank {
public:
	GLuint findOrReg(char* filename);

	TextureBank();

private:
	texmap _textures;

	GLuint find(char* filename);
	GLuint reg(char* filename);
};


static TextureBank texture_bank;


#endif /* UTIL_TEXTURE_BANK_H_ */
