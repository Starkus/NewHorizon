/*
 * wavefront.h
 *
 *  Created on: 24 de set. de 2015
 *      Author: starkus
 */

#ifndef UTIL_WAVEFRONT_H_
#define UTIL_WAVEFRONT_H_

#include <fstream>
#include <stdlib.h>
#include <map>
#include <string>
#include "../geometry/mesh.h"
#include "wavefront_mtl.h"


int loadObj(char* filename, Mesh* mesh);


#endif /* UTIL_WAVEFRONT_H_ */
