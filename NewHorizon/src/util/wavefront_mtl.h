/*
 * wavefront_mtl.h
 *
 *  Created on: 28 de oct. de 2015
 *      Author: starkus
 */

#ifndef UTIL_WAVEFRONT_MTL_H_
#define UTIL_WAVEFRONT_MTL_H_

#include <string>
#include <fstream>
#include <map>
#include "../geometry/mesh.h"


int loadMtl(const char* filename, Mesh* mesh, std::map<std::string, unsigned short>* matIndexes);


#endif /* UTIL_WAVEFRONT_MTL_H_ */
