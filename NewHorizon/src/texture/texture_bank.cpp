/*
 * texture_bank.cpp
 *
 *  Created on: 8 de ene. de 2016
 *      Author: starkus
 */




#include "texture_bank.h"

#include <stdio.h>



TextureBank::TextureBank()
{
}

GLuint TextureBank::reg(char *filename)
{

	printf("Tryna register: %s\n", filename);

	texture tex(filename);

	//char name[32];
	//removeLocation((const char*) filename, name);



	std::string name = filename;
	_textures[name] = tex;

	printf("Texture registered: %s\n", name.c_str());

	return tex.id;
}

GLuint TextureBank::find(char* filename)
{
	printf ("Looking for: %s\n", filename);
	std::string str = filename;
	std::map<std::string, texture>::iterator iter = _textures.find(str);

	if (iter != _textures.end())
		return iter->second.id;

	else return NULL_TEXTURE;
}

GLuint TextureBank::findOrReg(char* filename)
{
	GLuint found = find(filename);

	if (found == NULL_TEXTURE)
		return reg(filename);

	printf ("Texture found: %s\n", filename);
	return found;
}
