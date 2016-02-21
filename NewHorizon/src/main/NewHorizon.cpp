//============================================================================
// Name        : NewHorizon.cpp
// Author      : Starkus
// Version     : 0.01a
// Copyright   : Fuck it, free to use & reproduce
// Description : NewHorizon core file, Ansi-style
//============================================================================


#include <windows.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "../scene/camera.h"
#include "../scene/light.h"
#include "../scene/object.h"
#include "../geometry/mesh.h"
#include "../geometry/vbo.hpp"
#include "../texture/texture_bank.h"
#include "../primitives/box.h"
#include "../util/png.h"
#include "../util/wavefront.h"
#include "../shader/shader.h"

#define W_WIDTH 800
#define W_HEIGHT 600

#define RADIANS(i) i * 2 * 3.1415 / 360.0


int window;

long timer = 0;

GLuint programID;

bool left_button = false;
bool right_button = false;
int last_x, last_y;
float zoom = 5;

Camera camera;
LightSource light0 = LightSource(GL_LIGHT0);

Mesh mesh;
GLuint vboi = 0;
GLuint iboi = 0;
VBO vbo;
Object obj((char*) "car", &vbo);

GLuint test_texture;


glm::mat4 projection, view, model;
glm::vec4 lightPos, lightDiff, lightSpec;
// Uniforms
GLuint uTex;
GLuint uProjection, uView, uModel;
GLuint uLightPos, uLightDiff, uLightSpec;
GLuint uCameraPosition;

void libpng_version() {
	fprintf(stderr, "   Compiled with libpng %s; using libpng %s. \n",
			PNG_LIBPNG_VER_STRING, png_libpng_ver);
}


void init() {

	camera.position[2] = 15;

	libpng_version();

	light0.slot = GL_LIGHT0;
	light0.setDiffuse(1.0, 1.0, 1.0, 1.0);
	light0.setPosition(0.0, 0.0, 1.0, 0.0);
	light0.load();
	light0.enable();

	glewInit();

	loadObj((char*) "models/350z.obj", &mesh);
	VBOfromMesh(vbo, mesh);

	vbo.generate();

	int w, h;
	test_texture = texture_bank.findOrReg((char*) "textures/350z/vinyls.png");
	//test_texture = PNG_load((const char*) "textures/vinyls.png", &w, &h);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, test_texture);

	programID = loadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	glUseProgram(programID);

	uTex = glGetUniformLocation(programID, "texDiff");
	glUniform1i(uTex, 0);

	uProjection = glGetUniformLocation(programID, "projection");
	uView = glGetUniformLocation(programID, "view");
	uModel = glGetUniformLocation(programID, "model");

	uLightPos = glGetUniformLocation(programID, "lightPos");
	uLightDiff = glGetUniformLocation(programID, "lightDiff");
	uLightSpec = glGetUniformLocation(programID, "lightSpec");

	uCameraPosition = glGetUniformLocation(programID, "cameraPosition");

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_DEPTH_TEST);
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		left_button = (state == GLUT_DOWN);
	}
	if (button == GLUT_RIGHT_BUTTON) {
		right_button = (state == GLUT_DOWN);
	}
}

void movement(int x, int y) {
	if (left_button) {
		camera.orientation[0] -= (last_y - y) / 70.0;
		camera.orientation[2] += (last_x - x) / 80.0;
	}
	else if (right_button) {
		camera.position[2] -= (last_y - y) / 16.0;
	}
	last_x = x;
	last_y = y;
}
void passiveMovement(int x, int y) {
	last_x = x;
	last_y = y;
}

void display() {

	float fov = RADIANS(70.0);
	float aspect = (float)W_WIDTH / (float)W_HEIGHT;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	projection = glm::perspective(fov, aspect, 0.1f, 100.0f);
	camera.viewMatrix(view);

	lightPos = glm::vec4(1, 0, 1, 0);
	lightDiff = glm::vec4(0.8, 0.8, 0.8, 1);
	lightSpec = glm::vec4(1, 1, 1, 0);

	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &view[0][0]);

	glUniform4fv(uLightPos, 1, &lightPos[0]);
	glUniform4fv(uLightDiff, 1, &lightDiff[0]);
	glUniform4fv(uLightSpec, 1, &lightSpec[0]);

	glUniform3fv(uCameraPosition, 1, &(camera.position)[0]);


	obj.rotation[2] = (float)timer / 5000.0;
	obj.draw(programID, projection * view, uModel);


	glutSwapBuffers();
}

void update() {
	timer++;

	display();
}

int start(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	window = glutCreateWindow("C++!");

	glutIdleFunc(update);
	glutMouseFunc(mouse);
	glutMotionFunc(movement);
	glutPassiveMotionFunc(passiveMovement);
	glutDisplayFunc(display);
	init();
	glutMainLoop();


	return 0;
}
