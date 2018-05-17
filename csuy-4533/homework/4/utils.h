#ifndef INTERACTIVE_CG_UTILS_H
#define INTERACTIVE_CG_UTILS_H


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Angel-yjc.h"


using namespace std;


typedef struct Entity {
	vec4* vertices;
	vec4* colors;
	vec4* normals;
	vec2* textures;

	vec4* velocities;

	GLuint buffer;

	int size;
} Entity;


typedef struct Light {
	vec4 position;
	vec4 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	float attenuationConstant;
	float attenuationLinear;
	float attenuationQuadratic;

	float shininess;

	float exponent;
	float angle;
} Light;


void drawObject(GLuint, int, GLuint);

void drawParticles(GLuint, int, GLuint);

void readFile(const string&, const string&, vector<vec4>&, vector<vec4>&);

float distance(const vec4&, const vec4&);


#endif
