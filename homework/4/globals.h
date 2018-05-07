#ifndef INTERACTIVE_CG_GLOBALS_H
#define INTERACTIVE_CG_GLOBALS_H


#include "utils.h"


bool flagAnimation = false;
bool flagStarted = false;
bool flagShadow = true;
bool flagShading = false;
bool flagWire = false;
bool flagLight = true;
bool flagLightType = false;
int flagFogType = false;
bool flagShadowBlend = false;
bool flagFloorTexture = false;

GLuint program;

vec4 originalEye(7, 3, -10, 1);
vec4 eye = originalEye;
GLuint aspect;

Light ambientLight = {
	.position = vec4(0),
	.direction = vec4(0),

	.ambient = vec4(1, 1, 1, 1),
	.diffuse = vec4(0),
	.specular = vec4(0)
};

Light directionalLight = {
	.position = vec4(0),
	.direction = vec4(0.1, 0, -1, 0),

	.ambient = vec4(0, 0, 0, 1),
	.diffuse = vec4(0.8, 0.8, 0.8, 1),
	.specular = vec4(0.2, 0.2, 0.2, 1),
};

Light pointLight = {
	.position = vec4(-14, 12, -3, 1),
	.direction = vec4(0),

	.ambient = vec4(0, 0, 0, 1),
	.diffuse = vec4(1, 1, 1, 1),
	.specular = vec4(1, 1, 1, 1),

	.attenuationConstant = 2,
	.attenuationLinear = 0.01,
	.attenuationQuadratic = 0.01
};

Light spotLight = {
	.position = vec4(-14, 12, -3, 1),
	.direction = vec4(-6, 0, -4.5, 1),

	.ambient = vec4(0, 0, 0, 1),
	.diffuse = vec4(1, 1, 1, 1),
	.specular = vec4(1, 1, 1, 1),

	.attenuationConstant = 2,
	.attenuationLinear = 0.01,
	.attenuationQuadratic = 0.01,

	.shininess = 0,

	.exponent = 15,
	.angle = 20
};

Entity _fog;
vec4 fogColor(0.7, 0.7, 0.7, 0.5);
float fogStart = 0;
float fogEnd = 18;
float fogDensity = 0.09;


Entity _floor;
vec4 floorColor(0, 1, 0, 1);
vec4 floorVertices[4] = {
	vec4(5, 0, 8, 1),
	vec4(5, 0, -4, 1),
	vec4(-5, 0, -4, 1),
	vec4(-5, 0, 8, 1)
};
vec2 floorTextures[4] = {
	vec2(6, 5),
	vec2(0, 5),
	vec2(0, 0),
	vec2(6, 0)
};
Light floorLight = {
	.position = vec4(0),
	.direction = vec4(0),

	.ambient = vec4(0.2, 0.2, 0.2, 1),
	.diffuse = vec4(0, 1, 0, 1),
	.specular = vec4(0, 0, 0, 1)
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
Light sphereLight = {
	.position = vec4(0),
	.direction = vec4(0),

	.ambient = vec4(0.2, 0.2, 0.2, 1),
	.diffuse = vec4(1, 0.84, 0, 1),
	.specular = vec4(1, 0.84, 0, 1),

	.attenuationConstant = 0,
	.attenuationLinear = 0,
	.attenuationQuadratic = 0,

	.shininess = 125
};

vec4* sphereShadeFlat;
vec4* sphereShadeSmooth;

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


#endif
