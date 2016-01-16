/*
 * wavefront.cpp
 *
 *  Created on: 24 de set. de 2015
 *      Author: starkus
 */


#include "wavefront.h"

using namespace std;


#define COMMENT_BIT	128		// 0b 1000 0000
#define FUNC_BITS	112		// 0b 0111 0000
#define PARAM_BITS	12		// 0b 0000 1100
#define SUB_BITS	3		// 0b 0000 0011

#define OTHER		0		// 0b 0000 0000
#define VERTEX		16		// 0b 0001 0000
#define NORMAL		32		// 0b 0010 0000
#define UV			48		// 0b 0011 0000
#define FACE		64		// 0b 0100 0000
#define MATS_FILE	80		// 0b 0101 0000
#define USING_MAT	96		// 0b 0110 0000
#define OBJ_NAME	112		// 0b 0111 0000

#define INSTRUCTION	0		// 0b 0000 0000
#define FIRST_PAR	4		// 0b 0000 0100
#define SECOND_PAR	8		// 0b 0000 1000
#define THIRD_PAR	12		// 0b 0000 1100

#define NO_SUB		0		// 0b 0000 0000
#define FIRST_SUB	1		// 0b 0000 0001
#define SECOND_SUB	2		// 0b 0000 0010
#define THIRD_SUB	3		// 0b 0000 0011


#define instruction(s) (line.compare(s) == 0)
#define onInstruction(s) ((state & FUNC_BITS) == s && (state & PARAM_BITS) != INSTRUCTION)


void getFaceIndexes(string line, unsigned int* vert, unsigned int* uv, unsigned int* nor) {

	string substring;
	std::size_t pos = -1;

	for (char i = 0; i < 3; i++) {
		substring = line.substr(pos+1, line.find('/', pos+1));
		if (!substring.empty()) {
			if (i == 0)
				*vert = atoi(substring.c_str()) - 1;
			else if (i == 1)
				*uv = atoi(substring.c_str()) - 1;
			else if (i == 2)
				*nor = atoi(substring.c_str()) - 1;
		}
		pos = line.find('/', pos+1);
	}
}

int loadObj(char* filename, Mesh* mesh) {

	#define VERTS mesh->vertices
	#define NORMS mesh->normals
	#define FACES mesh->faces
	#define UVS mesh->uvs

	ifstream objFile;
	objFile.open(filename);

	map<string, unsigned short> matIndexes;

	if (objFile.is_open()) {

		string line;
		char state;

		unsigned int vert, nor,	uv;
		unsigned short material;

		while (objFile.good()) {

			if instruction("mtllib") {

				state = MATS_FILE;
			}
			else if instruction("vt") {

				state = UV;
			}

			else if instruction("vn") {

				state = NORMAL;
			}

			else if instruction("v") {

				state = VERTEX;
			}

			else if instruction("f") {

				state = FACE;
			}

			else if instruction("usemtl") {

				state = USING_MAT;
			}


			////	MATLIB		///////////////////////////////////////////
			else if onInstruction(MATS_FILE) {

				string name = "models/" + line;

				loadMtl(name.c_str(), mesh, &matIndexes);
			}


			////	VERTEX		///////////////////////////////////////////
			else if onInstruction(VERTEX) {

				Vertex vertex;


				if ((state & PARAM_BITS) == FIRST_PAR) {

					vertex.x = atof(line.c_str());

					state = VERTEX | SECOND_PAR;
				}
				else if ((state & PARAM_BITS) == SECOND_PAR) {

					vertex.y = atof(line.c_str());

					state = VERTEX | THIRD_PAR;
				}
				else if ((state & PARAM_BITS) == THIRD_PAR) {

					vertex.z = atof(line.c_str());

					mesh->vertices.push_back(vertex);

					state = 0;
				}
			}


			////	NORMAL		///////////////////////////////////////////
			else if onInstruction(NORMAL) {

				Vertex vertex;

				switch (state & PARAM_BITS) {
				case (FIRST_PAR):

					vertex.x = atof(line.c_str());

					state = NORMAL | SECOND_PAR;
					break;

				case (SECOND_PAR):

					vertex.y = atof(line.c_str());

					state = NORMAL | THIRD_PAR;
					break;
				case (THIRD_PAR):

					vertex.z = atof(line.c_str());

					mesh->normals.push_back(vertex);

					state = 0;
					break;
				}
			}


			////	UV VERTEX		///////////////////////////////////////////
			else if onInstruction(UV) {

				VertexUV vertex;


				if ((state & PARAM_BITS) == FIRST_PAR) {

					vertex.u = atof(line.c_str());

					state = UV | SECOND_PAR;
				}
				else if ((state & PARAM_BITS) == SECOND_PAR) {

					vertex.v = atof(line.c_str());

					mesh->uvs.push_back(vertex);

					state = 0;
				}
			}


			////	FACE		///////////////////////////////////////////
			else if onInstruction(FACE) {

				Face face;

				vert = uv = nor = 0;


				switch (state & PARAM_BITS) {
				case (FIRST_PAR):

					getFaceIndexes(line, &vert, &uv, &nor);

					face.vertex[0] = vert;
					face.uv[0] = uv;
					face.normal[0] = nor;

					state = FACE | SECOND_PAR;
					break;

				case (SECOND_PAR):

					getFaceIndexes(line, &vert, &uv, &nor);

					face.vertex[1] = vert;
					face.uv[1] = uv;
					face.normal[1] = nor;

					state = FACE | THIRD_PAR;
					break;

				case (THIRD_PAR):

					getFaceIndexes(line, &vert, &uv, &nor);

					face.vertex[2] = vert;
					face.uv[2] = uv;
					face.normal[2] = nor;

					face.material = material;

					mesh->faces.push_back(face);

					state = 0;
					break;
				}
			}

			////	USING MATERIAL		////////////////////////////////////
			else if onInstruction(USING_MAT) {

				material = matIndexes.at(line);

				state = 0;
			}

			if ((state & PARAM_BITS) == INSTRUCTION)
				state = (state & FUNC_BITS) | FIRST_PAR;

			objFile >> line;
		}

	} else {
		return -1;
	}

	objFile.close();

	return 0;
}
