/*
 * box.cpp
 *
 *  Created on: 20 de set. de 2015
 *      Author: starkus
 */


#include "../geometry/mesh.h"
#include <algorithm>
#include <vector>

void genBox(Mesh* mesh, float size) {

	#define VERTS mesh->vertices
	#define NORMS mesh->normals
	#define FACES mesh->faces
	#define UVS mesh->uvs

	VERTS = std::vector<Vertex>(8, Vertex());
	NORMS = std::vector<Vertex>(6, Vertex());
	UVS = std::vector<VertexUV>(4, VertexUV());
	FACES = std::vector<Face>(12, Face());


	VERTS.at(0).x = VERTS.at(1).x = VERTS.at(2).x = VERTS.at(3).x = -size;
	VERTS.at(4).x = VERTS.at(5).x = VERTS.at(6).x = VERTS.at(7).x =  size;
	VERTS.at(0).y = VERTS.at(1).y = VERTS.at(4).y = VERTS.at(5).y = -size;
	VERTS.at(2).y = VERTS.at(3).y = VERTS.at(6).y = VERTS.at(7).y =  size;
	VERTS.at(0).z = VERTS.at(3).z = VERTS.at(4).z = VERTS.at(7).z =  size;
	VERTS.at(1).z = VERTS.at(2).z = VERTS.at(5).z = VERTS.at(6).z = -size;

	NORMS.at(0).x = -1.0;	NORMS.at(0).y =  0.0;	NORMS.at(0).z =  0.0;
	NORMS.at(1).x =  0.0;	NORMS.at(1).y =  1.0;	NORMS.at(1).z =  0.0;
	NORMS.at(2).x =  1.0;	NORMS.at(2).y =  0.0;	NORMS.at(2).z =  0.0;
	NORMS.at(3).x =  0.0;	NORMS.at(3).y = -1.0;	NORMS.at(3).z =  0.0;
	NORMS.at(4).x =  0.0;	NORMS.at(4).y =  0.0;	NORMS.at(4).z =  1.0;
	NORMS.at(5).x =  0.0;	NORMS.at(5).y =  0.0;	NORMS.at(5).z = -1.0;

	UVS.at(0).u = UVS.at(3).u = 0.0;
	UVS.at(1).u = UVS.at(2).u = 1.0;
	UVS.at(0).v = UVS.at(1).v = 0.0;
	UVS.at(2).v = UVS.at(3).v = 1.0;


	int v0[] = {0, 1, 2};
	int v1[] = {0, 3, 2};
	int v2[] = {3, 2, 6};
	int v3[] = {3, 7, 6};
	int v4[] = {7, 6, 5};
	int v5[] = {7, 4, 5};
	int v6[] = {4, 5, 1};
	int v7[] = {4, 0, 1};
	int v8[] = {5, 6, 2};
	int v9[] = {5, 1, 2};
	int vA[] = {7, 4, 0};
	int vB[] = {7, 3, 0};

	std::copy(v0, v0+3, FACES.at(0).vertex);
	std::copy(v1, v1+3, FACES.at(1).vertex);
	std::copy(v2, v2+3, FACES.at(2).vertex);
	std::copy(v3, v3+3, FACES.at(3).vertex);
	std::copy(v4, v4+3, FACES.at(4).vertex);
	std::copy(v5, v5+3, FACES.at(5).vertex);
	std::copy(v6, v6+3, FACES.at(6).vertex);
	std::copy(v7, v7+3, FACES.at(7).vertex);
	std::copy(v8, v8+3, FACES.at(8).vertex);
	std::copy(v9, v9+3, FACES.at(9).vertex);
	std::copy(vA, vA+3, FACES.at(10).vertex);
	std::copy(vB, vB+3, FACES.at(11).vertex);

	for (int i = 0; i < 12; i++) {
		FACES.at(i).normal[0] = FACES.at(i).normal[1] = FACES.at(i).normal[2] = (int)(i/2);
	}
}
