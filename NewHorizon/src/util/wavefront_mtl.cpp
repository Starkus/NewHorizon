/*
 * wavefront_mtl.cpp
 *
 *  Created on: 28 de oct. de 2015
 *      Author: starkus
 */


#include "wavefront_mtl.h"

using namespace std;


#define COMMENT_BIT	128		// 0b 1000 0000
#define FUNC_BITS	124		// 0b 0111 1100
#define PARAM_BITS	3		// 0b 0000 0011

#define OTHER		0		// 0b 0000 0000
#define NEWMTL		4		// 0b 0000 0100
#define AMBIENT		8		// 0b 0000 1000
#define DIFFUSE		12		// 0b 0000 1100
#define SPECULAR	16		// 0b 0001 0000
#define EMITION		20		// 0b 0001 0100
#define PHONG		24		// 0b 0001 1000
#define REFRACTION	28		// 0b 0001 1100

#define MAP_DIFF	32		// 0b 0010 0000
#define MAP_SPEC	36		// 0b 0010 0100
#define MAP_EMIT	40		// 0b 0010 1000
#define MAP_ALPHA	44		// 0b 0010 1100
#define MAP_NOR		48		// 0b 0011 0000
#define MAP_REFL	52		// 0b 0011 0100
#define SHADERTYPE	56		// 0b 0011 1000
#define ALPHA		60		// 0b 0011 1100

#define INSTRUCTION	0		// 0b 0000 0000
#define FIRST_PAR	1		// 0b 0000 0001
#define SECOND_PAR	2		// 0b 0000 0010
#define THIRD_PAR	3		// 0b 0000 0011


#define instruction(s) (line.compare(s) == 0)
#define onInstruction(s) ((state & FUNC_BITS) == s && (state & PARAM_BITS) != INSTRUCTION)


int loadMtl(const char* filename, Mesh* mesh, map<string, unsigned short>* matIndexes) {

	#define MATS mesh->materials

	ifstream mtlFile;
	mtlFile.open(filename);

	Material* current;
	unsigned short position = 0;

	glm::vec3 color;


	if (mtlFile.is_open()) {

		string line;
		char state;

		while (mtlFile.good()) {

			if instruction("newmtl") {

				state = NEWMTL;
			}
			else if instruction("Ka") {

				state = AMBIENT;
			}
			else if instruction("Kd") {

				state = DIFFUSE;
			}
			else if instruction("Ks") {

				state = SPECULAR;
			}
			else if instruction("Ke") {

				state = EMITION;
			}
			else if instruction("Ns") {

				state = PHONG;
			}
			else if instruction("d") {

				state = ALPHA;
			}
			else if instruction("map_Kd") {

				state = MAP_DIFF;
			}
			else if instruction("map_Ks") {

				state = MAP_SPEC;
			}
			else if instruction("map_Ke") {

				state = MAP_EMIT;
			}
			else if instruction("map_d") {

				state = MAP_ALPHA;
			}
			else if instruction("map_Bump") {

				state = MAP_NOR;
			}


			////	NEWMTL		///////////////////////////////////////////
			else if onInstruction(NEWMTL) {

				// Add to map, so it's accessible by name
				matIndexes->insert(pair<string, unsigned short>(line, position));

				Material mat;
				MATS.push_back(mat);

				current = &(MATS[position]);

				position++;
			}


			////	COLORS		///////////////////////////////////////////
			else if onInstruction(DIFFUSE) {

				if ((state & PARAM_BITS) == FIRST_PAR) {

					color.r = atof(line.c_str());

					state = DIFFUSE | SECOND_PAR;
				}
				else if ((state & PARAM_BITS) == SECOND_PAR) {

					color.g = atof(line.c_str());

					state = DIFFUSE | THIRD_PAR;
				}
				else if ((state & PARAM_BITS) == THIRD_PAR) {

					color.b = atof(line.c_str());

					current->colDiff = color;

					//cout << "COLOR " << color.r << ' ' << color.g << ' ' << color.b << endl;

					state = 0;
				}
			}

			else if onInstruction(SPECULAR) {

				if ((state & PARAM_BITS) == FIRST_PAR) {

					color.r = atof(line.c_str());

					state = SPECULAR | SECOND_PAR;
				}
				else if ((state & PARAM_BITS) == SECOND_PAR) {

					color.g = atof(line.c_str());

					state = SPECULAR | THIRD_PAR;
				}
				else if ((state & PARAM_BITS) == THIRD_PAR) {

					color.b = atof(line.c_str());

					current->colSpec = color;

					state = 0;
				}
			}

			else if onInstruction(PHONG) {

				if ((state & PARAM_BITS) == FIRST_PAR) {

					current->specInt = atof(line.c_str());
					state = 0;
				}
			}

			else if onInstruction(MAP_DIFF) {

				if ((state & PARAM_BITS) == FIRST_PAR) {

					current->texDiff = texture_bank.findOrReg((char*) line.c_str());
					state = 0;
				}
			}

			if ((state & PARAM_BITS) == INSTRUCTION)
				state = (state & FUNC_BITS) | FIRST_PAR;

			mtlFile >> line;
		}
	} else {
		return -1;
	}

	return 0;
}
