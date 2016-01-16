/*
 * texture_bank.cpp
 *
 *  Created on: 8 de ene. de 2016
 *      Author: starkus
 */




#include "texture_bank.h"


static GLuint registerTex(char *filename)
{
	texture tex(filename);

	//char name[32];
	//removeLocation((const char*) filename, name);



	std::string name = filename;
	_textures.at(name) = tex;

	return tex.id;
}

static GLuint findTex(std::string name)
{
	std::map<std::string, texture>::iterator iter = _textures.find(name);

	if (iter != _textures.end())
		return iter->second.id;

	else return -1;
}

GLuint findOrReg(char* filename)
{
	std::string name = filename;

	GLuint found = findTex(name);

	if (found == NULL_TEXTURE)
		return registerTex(filename);

	return found;
}
