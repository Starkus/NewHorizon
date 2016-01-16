/*
 * mesh.h
 *
 *  Created on: 20 de set. de 2015
 *      Author: starkus
 */

#ifndef MESH_MESH_H
#define MESH_MESH_H

#include "../geometry/geometry.h"
#include <vector>

#include <glm/glm.hpp>
#include <GL/glut.h>



struct Material {

	glm::vec3 colDiff, colSpec, colAmb;
	float alpha, specInt;

	GLuint texDiff, texSpec;
	float texFacDiff, texFacSpec;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<Vertex> normals;
	std::vector<VertexUV> uvs;
	std::vector<Face> faces;

	std::vector<Material> materials;

	//~Mesh();
};


#endif /* MESH_MESH_H */
