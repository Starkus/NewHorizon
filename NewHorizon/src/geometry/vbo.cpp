/*
 * vbo.cpp
 *
 *  Created on: 26 de set. de 2015
 *      Author: starkus
 */



#include "vbo.hpp"

#include <stdio.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


bool getSimilar(VBOVertex& vVert, std::map<VBOVertex, unsigned int> &outIndex, unsigned int& result) {

	std::map<VBOVertex, unsigned int>::iterator iter = outIndex.find(vVert);
	if (iter == outIndex.end()) {
		return false;
	} else {
		result = iter->second;
		return true;
	}
}


void VBOfromMesh(VBO& vbo, Mesh& mesh) {
	std::map<VBOVertex, unsigned int> outIndex;

	float u, v;

	vbo.materials = mesh.materials;
	unsigned short currentMat = -1;

	for (unsigned int i = 0; i < mesh.faces.size(); i++) {
		for (unsigned short j = 0; j < 3; j++) {

			Face& f = mesh.faces.at(i);

			if (f.uv[j] == (unsigned int) -1) {
				u = 0;
				v = 0;
			} else {
				u = mesh.uvs.at(f.uv[j]).u;
				v = mesh.uvs.at(f.uv[j]).v;
			}
			VBOVertex vVert = {
					mesh.vertices.at(f.vertex[j]).x,
					mesh.vertices.at(f.vertex[j]).y,
					mesh.vertices.at(f.vertex[j]).z,
					mesh.normals.at(f.normal[j]).x,
					mesh.normals.at(f.normal[j]).y,
					mesh.normals.at(f.normal[j]).z,
					u,
					v,
					mesh.materials.at(f.material)
			};

			unsigned int index;
			bool found = getSimilar(vVert, outIndex, index);

			if (found) {
				vbo.indices.push_back(index);
			} else {
				vbo.verts.push_back(vVert);
				unsigned int newindex = (unsigned int) vbo.verts.size() - 1;
				vbo.indices.push_back(newindex);
				outIndex[vVert] = newindex;

				if (currentMat != f.material) {
					vbo.material_indices.push_back(vbo.indices.size() - 1);
					vbo.material_orders.push_back(currentMat);
					currentMat = f.material;
				}
			}
		}
	}
}


VBO::VBO(/*GLuint vbo, GLuint ibo*/) {
	vbo_id = 0;
	ibo_id = 0;
}
VBO::~VBO() {
	glDeleteBuffers(1, &vbo_id);
	glDeleteBuffers(1, &ibo_id);
}

void VBO::generate() {

	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VBOVertex)*verts.size(), &verts[0].x, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
}

void VBO::draw(GLuint program) {
	using namespace glm;

	GLuint uDiff = glGetUniformLocation(program, "matDiffuse");
	GLuint uSpec = glGetUniformLocation(program, "matSpecular");

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(VBOVertex), BUFFER_OFFSET(0));
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(VBOVertex), BUFFER_OFFSET(12));
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(VBOVertex), BUFFER_OFFSET(24));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);

	for (uint m = 0; m < materials.size(); ++m) {

		Material& mat = materials[material_orders[m]];

		vec3 dif = mat.colDiff;
		glUniform3f(uDiff, dif.r, dif.g, dif.b);

		vec3 spe = mat.colSpec;
		glUniform4f(uSpec, spe.r, spe.g, spe.b, mat.specInt);

		if (mat.texDiff != NULL_TEXTURE)
			glBindTexture(GL_TEXTURE_2D, mat.texDiff);


		GLuint end = material_indices[m];
		glDrawElements(GL_TRIANGLES, end, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	}
}
