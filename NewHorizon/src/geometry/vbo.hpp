/*
 * vbo.h
 *
 *  Created on: 26 de set. de 2015
 *      Author: starkus
 */

#ifndef MESH_VBO_H
#define MESH_VBO_H

#include <GL/glew.h>

#include <vector>
#include <map>
#include <string.h>

#include "geometry.h"
#include "mesh.h"
#include "../texture/texture.h"

using namespace std;

struct VBOVertex {
	GLfloat x, y, z;
	GLfloat nx, ny, nz;
	GLfloat u, v;
	Material material;

	bool operator< (const VBOVertex that) const {
		return memcmp((void*) this, (void*) &that, sizeof(VBOVertex))>0;
	};
};

class VBO {
private:
	GLuint vbo_id;
	GLuint ibo_id;
public:
	vector<VBOVertex> verts;
	vector<unsigned int> indices;
	vector<Material> materials;
	vector<unsigned short> material_indices;
	vector<unsigned short> material_orders;

	VBO(/*GLuint vbo, GLuint ibo*/);
	~VBO();

	void generate();
	void draw(GLuint program);
};


void VBOfromMesh(VBO &vbo, Mesh &mesh);


#endif /* MESH_VBO_H */
