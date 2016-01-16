/*
 * light.cpp
 *
 *  Created on: 20 de set. de 2015
 *      Author: starkus
 */


#include <GL/gl.h>
#include "light.h"

LightSource::LightSource(unsigned int s) : slot(s), position(), diffuse() {
}

void LightSource::setPosition(float x, float y, float z, float w) {
	position[0] = x;
	position[1] = y;
	position[2] = z;
	position[3] = w;
}

void LightSource::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}

void LightSource::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}

void LightSource::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}

void LightSource::load() {

	glLightfv(slot, GL_POSITION, position);
	glLightfv(slot, GL_AMBIENT, ambient);
	glLightfv(slot, GL_DIFFUSE, diffuse);
	glLightfv(slot, GL_SPECULAR, specular);
}

void LightSource::enable() {

	glEnable(slot);
}
