#ifndef INTERACTIVE_CG_GLOBALS_H
#define INTERACTIVE_CG_GLOBALS_H


#include "utils.h"

bool flagAnimation = false;
bool flagStarted = false;
bool flagShadow = true;
bool flagShading = false;
bool flagWire = false;
bool flagLight = true;

GLuint program;

vec4 originalEye(7, 3, -10, 1);
vec4 eye = originalEye;
GLuint aspect;

Entity _floor;
vec4 floorColor(0, 1, 0, 1);
vec4 floorVertices[4] = {
	vec4(5, 0, 8, 1),
	vec4(5, 0, -4, 1),
	vec4(-5, 0, -4, 1),
	vec4(-5, 0, 8, 1)
};

Entity _axes;
vec4 axesColors[3] = {
	vec4(1, 0, 0, 1),
	vec4(1, 0, 1, 1),
	vec4(0, 0, 1, 1)
};
vec4 axesVertices[9] = {
	vec4(0, 0, 0, 1),
	vec4(10, 0, 0, 1),
	vec4(20, 0, 0, 1),
	vec4(0, 0, 0, 1),
	vec4(0, 10, 0, 1),
	vec4(0, 20, 0, 1),
	vec4(0, 0, 0, 1),
	vec4(0, 0, 10, 1),
	vec4(0, 0, 20, 1)
};

Entity _sphere;
vec4 sphereColor(1, 0.84, 0, 1);
vector<vec4> sphereVertices;

vec4 sphereMovementVectors[3];
vec4 sphereMovementVertices[3] = {
	vec4(-4, 1, 4, 1),
	vec4(3, 1, -4, 1),
	vec4(-3, 1, -3, 1)
};
vec4 sphereRotationAxes[3];
vec4 sphereCenter;
int sphereIndex = 0;
float sphereRadius = 1;
float sphereRate = 1;
mat4 sphereRotationMatrix(
	vec4(1, 0, 0, 0),
	vec4(0, 1, 0, 0),
	vec4(0, 0, 1, 0),
	vec4(0, 0, 0, 1)
);


Entity _shadow;
vec4 shadowColor(0.25, 0.25, 0.25, 0.65);
vector<vec4> shadowVertices;

vec4 lightPosition(-14, -12, -3, 1);


#endif
