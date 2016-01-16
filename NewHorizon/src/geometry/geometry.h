/*
 * vertex.h
 *
 *  Created on: 20 de set. de 2015
 *      Author: starkus
 */

#ifndef GEOMETRY_VERTEX_H
#define GEOMETRY_VERTEX_H


struct Vertex {
	float x, y, z;
};

struct VertexUV {
	float u, v;
};

struct Face {
	unsigned int vertex[3];
	unsigned int normal[3];
	unsigned int uv[3];
	unsigned short material;
};

#endif /* GEOMETRY_VERTEX_H */
