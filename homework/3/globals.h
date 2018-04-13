#ifndef INTERACTIVE_CG_GLOBALS_H
#define INTERACTIVE_CG_GLOBALS_H


#include "utils.h"


GLuint program;
vec4 originalEye(7, 3, -10, 1);
vec4 eye = originalEye;
bool animation;
bool started;
GLuint aspect;

vec3 colorSphere(1, 0.84, 0);
vec3 colorFloor(0, 1, 0);
vec3 axisColors[3] = {
	vec3(1, 0, 0),
	vec3(1, 0, 1),
	vec3(0, 0, 1)
};

vec3 floorVertices[4] = {
	vec3(5, 0, 8),
	vec3(5, 0, -4),
	vec3(-5, 0, -4),
	vec3(-5, 0, 8)
};

Entity _floor;

Entity _axes;

vec3 pathPoints[3] = {
	vec3(-4, 1, 4),
	vec3(3, 1, -4),
	vec3(-3, 1, -3)
};
vector<vec3> spherePoints;
vec3 movementVectors[3];
vec3 rotationAxes[3];
vec3 sphereCenter;
int sphereIndex = 0;
float radius = 1;
float angle = 0;
float rate = 1;
mat4 rotationMatrix(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
Entity _sphere;


#endif
