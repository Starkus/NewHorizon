/*
 * loadShader.cpp
 *
 *  Created on: 26 de set. de 2015
 *      Author: starkus
 */


#include <stdio.h>

#include <GL/glew.h>

#include <vector>
#include <string>
#include <fstream>


using namespace std;


GLuint loadShaders(const char* vertex_filename, const char* fragment_filename) {

	GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read vertex shader file
	string vertCode;
	ifstream vertStream(vertex_filename, ios::in);
	if (vertStream.is_open()) {
		string line = "";
		while (getline(vertStream, line))
			vertCode += '\n' + line;
		vertStream.close();
	}

	// Read fragment shader file
	string fragCode;
	ifstream fragStream(fragment_filename, ios::in);
	if (fragStream.is_open()) {
		string line = "";
		while (getline(fragStream, line))
			fragCode += '\n' + line;
		fragStream.close();
	}

	GLint result = GL_FALSE;
	int info_log_length;

	// Compile vertex shader
	printf("Compiling shader: %s\n", vertex_filename);
	char const *vertSource = vertCode.c_str();
	glShaderSource(vertID, 1, &vertSource, NULL);
	glCompileShader(vertID);

	// Check vertex shader
	glGetShaderiv(vertID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &info_log_length);
	vector<char> vertShaderErrorMessage(info_log_length);
	glGetShaderInfoLog(vertID, info_log_length, NULL, &vertShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vertShaderErrorMessage[0]);


	// Compile fragment shader
	printf("Compiling shader: %s\n", fragment_filename);
	char const *fragSource = fragCode.c_str();
	glShaderSource(fragID, 1, &fragSource, NULL);
	glCompileShader(fragID);

	// Check fragment shader
	glGetShaderiv(fragID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragID, GL_INFO_LOG_LENGTH, &info_log_length);
	vector<char> fragShaderErrorMessage(info_log_length);
	glGetShaderInfoLog(fragID, info_log_length, NULL, &fragShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &fragShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertID);
	glAttachShader(programID, fragID);
	glLinkProgram(programID);

	// Check program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &info_log_length);
	vector<char> progErrorMessage(max(info_log_length, int(1)));
	glGetProgramInfoLog(programID, info_log_length, NULL, &progErrorMessage[0]);
	fprintf(stdout, "%s\n", &progErrorMessage[0]);

	glDeleteShader(vertID);
	glDeleteShader(fragID);

	return programID;
}
