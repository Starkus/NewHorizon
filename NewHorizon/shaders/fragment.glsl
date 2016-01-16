#version 330 core

out vec4 color;

// Textures
uniform sampler2D tex;

uniform vec4 lightPos;
uniform vec4 lightDiff;
uniform vec4 lightSpec;

// Camera
uniform vec3 cameraPosition;

uniform vec3 matDiffuse;
uniform vec4 matSpecular;

varying vec4 vVertex;
varying vec4 vViewVertex;
varying vec3 vNormal;
varying vec2 vUv;


vec4 diffuse() {
	float diffProd = max(0, dot(vNormal, vec3(lightPos)));
	vec4 lum = vec4(vec3(diffProd), 1.0);
	
	return lum * lightDiff * vec4(matDiffuse, 1.0);
}

vec4 specular() {

	vec4 lightNor = normalize(lightPos - vVertex);
	vec3 viewDirection = normalize(cameraPosition - vViewVertex.xyz);

	vec3 nor = vNormal;

	vec3 angle = normalize(viewDirection + lightNor.xyz);
	float Ispec = max(0.0, dot(nor, angle));
	Ispec = pow(Ispec, max(1.0, matSpecular.w)) * 2;
	vec3 spec = vec3(matSpecular.xyz * Ispec * lightSpec.xyz);
	
	return vec4(spec, 1.0);
}


void main() {

	color = diffuse() + specular();
	color = vec4(texture2D(tex, vUv));
}