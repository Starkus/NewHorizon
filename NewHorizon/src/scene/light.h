/*
 * light.h
 *
 *  Created on: 20 de set. de 2015
 *      Author: starkus
 */

#ifndef SCENE_LIGHT_H
#define SCENE_LIGHT_H

#include <GL/gl.h>

struct LightSource {
	unsigned int slot;

	float position[4];

	float ambient[4];
	float diffuse[4];
	float specular[4];

	LightSource(unsigned int slot);

	void setPosition(float x, float y, float z, float w);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);

	void load();
	void enable();
};


#endif /* SCENE_LIGHT_H */
