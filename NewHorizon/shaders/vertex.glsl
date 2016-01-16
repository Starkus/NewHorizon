#version 330 core

layout(location = 0) in vec3 vertPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec4 vVertex;
varying vec4 vViewVertex;
varying vec3 vNormal;
varying vec2 vUv;
varying vec3 vTVertex;


void main(){
	mat4 MVP = projection * view * model;
	mat4 modelView = model;

	gl_Position = MVP * vec4(vertPos, 1.0);
	
	vVertex = vec4(vertPos, 1.0);
	vViewVertex = vec4(modelView * vec4(vertPos, 1.0));
	
	vNormal = vec3(model * vec4(gl_Normal, 0));
	vUv = vec2(gl_MultiTexCoord0);
}