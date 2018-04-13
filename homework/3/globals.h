#ifndef INTERACTIVE_CG_GLOBALS_H
#define INTERACTIVE_CG_GLOBALS_H


#include "utils.h"

bool flagAnimation;
bool flagStarted;

GLuint program;

vec4 originalEye(7, 3, -10, 1);
vec4 eye = originalEye;
GLuint aspect;

Entity _floor;
vec3 floorColor(0, 1, 0);
vec3 floorVertices[4] = {
	vec3(5, 0, 8),
	vec3(5, 0, -4),
	vec3(-5, 0, -4),
	vec3(-5, 0, 8)
};

Entity _axes;
vec3 axesColors[3] = {
	vec3(1, 0, 0),
	vec3(1, 0, 1),
	vec3(0, 0, 1)
};
vec3 axesVertices[9] = {
	vec3(0, 0, 0),
	vec3(10, 0, 0),
	vec3(20, 0, 0),
	vec3(0, 0, 0),
	vec3(0, 10, 0),
	vec3(0, 20, 0),
	vec3(0, 0, 0),
	vec3(0, 0, 10),
	vec3(0, 0, 20)
};

Entity _sphere;
vec3 sphereColor(1, 0.84, 0);
vector<vec3> sphereVertices;

vec3 sphereMovementVectors[3];
vec3 sphereMovementVertices[3] = {
	vec3(-4, 1, 4),
	vec3(3, 1, -4),
	vec3(-3, 1, -3)
};
vec3 sphereRotationAxes[3];
vec3 sphereCenter;
int sphereIndex = 0;
float sphereRadius = 1;
float sphereRate = 1;
mat4 sphereRotationMatrix(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));


#endif
