/*
 * texture.cpp
 *
 *  Created on: 8 de ene. de 2016
 *      Author: starkus
 */


#include "texture.h"


/*	Copies from the original char array from the last
 *  '/' on up to null character, into target pointer.
 */
void removeLocation(const char* filename, char* target)
{
	int namei = 0;
	int ssize = 0;

	for (int i = 0; filename[i] != 0; ++i)
	{
		++ssize;

		/* Each '/' overrides the last one, so the last
		 * one's index is in namei at the end of loop.
		 */
		if (filename[i] == '\\' || filename[i] == '/')
			namei = i + 1;
	}

	memcpy(target, filename + namei, ssize - namei);
}


/*	Initializator loads the PNG, gets the name from
 *  the file name and sets the OpenGL ID to pass to
 *  the shader.
 */
texture::texture(const char* filename)
{
	id = PNG_load(filename, &width, &height);

	//removeLocation(filename, name);
	name = filename;
}
