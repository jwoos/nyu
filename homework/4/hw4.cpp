#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Angel-yjc.h"
#include "utils.h"
#include "texmap.h"
#include "globals.h"


using namespace std;


extern bool flagAnimation;
extern bool flagStarted;
extern bool flagShadow;
extern bool flagShading;
extern bool flagWire;
extern bool flagLight;
extern bool flagLightType;
extern int flagFogType;
extern bool flagShadowBlend;
extern bool flagFloorTexture;
extern bool flagFrame;
extern bool flagTextureOrientation;
extern bool flagSphereTexture;

extern GLuint program;

extern GLuint positionalLight;
extern GLuint uniformLight;

extern vec4 originalEye;
extern vec4 eye;
extern GLuint aspect;

extern Light ambientLight;
extern Light directionalLight;
extern Light pointLight;
extern Light spotLight;

extern Entity _floor;
extern vec4 floorColor;
extern vec4 floorVertices[4];
extern vec2 floorTextures[4];
extern Light floorLight;

extern Entity _axes;
extern vec4 axesColors[3];
extern vec4 axesVertices[9];

extern Entity _sphere;
extern vec4 sphereColor;
extern vector<vec4> sphereVertices;
extern Light sphereLight;

extern vec4* sphereShadeFlat;
extern vec4* sphereShadeSmooth;

extern vec4 sphereMovementVertices[3];
extern vec4 sphereMovementVectors[3];
extern vec4 sphereRotationAxes[3];
extern vec4 sphereCenter;
extern int sphereIndex;
extern float sphereRadius;
extern float sphereRate;
extern mat4 sphereRotationMatrix;

extern Entity _shadow;
extern vec4 shadowColor;
extern vector<vec4> shadowVertices;

extern vec4 fogColor;
extern float fogStart;
extern float fogEnd;
extern float fogDensity;


void texture(void) {
	image_set_up();

	GLuint texture1d;
	GLuint texture2d;

	// set up 1d texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texture1d);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_1D, texture1d);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, STRIPE_IMAGE_WIDTH, 0, GL_RGBA, GL_UNSIGNED_BYTE, TEXTURE_STRIPE_IMAGE);

	// set up 2d texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texture2d);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture2d);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_WIDTH, IMAGE_WIDTH, 0, GL_RGBA, GL_UNSIGNED_BYTE, TEXTURE_IMAGE);
}

// set up floor
void floor(void) {
	_floor.size = 6;
	_floor.vertices = new vec4[_floor.size];
	_floor.colors = new vec4[_floor.size];
	_floor.normals = new vec4[_floor.size];
	_floor.textures = new vec2[_floor.size];

	_floor.vertices[0] = floorVertices[0];
	_floor.vertices[1] = floorVertices[1];
	_floor.vertices[2] = floorVertices[2];
	_floor.vertices[3] = floorVertices[0];
	_floor.vertices[4] = floorVertices[2];
	_floor.vertices[5] = floorVertices[3];

	_floor.textures[0] = floorTextures[0];
	_floor.textures[1] = floorTextures[1];
	_floor.textures[2] = floorTextures[2];
	_floor.textures[3] = floorTextures[0];
	_floor.textures[4] = floorTextures[2];
	_floor.textures[5] = floorTextures[3];

	vec4 normal = normalize(cross(
		_floor.vertices[2] - _floor.vertices[3],
		_floor.vertices[0] - _floor.vertices[1]
	));

	for (int i = 0; i < _floor.size; i++) {
		_floor.colors[i] = floorColor;
		_floor.normals[i] = normal;
	}

	glGenBuffers(1, &_floor.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _floor.buffer);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _floor.size * 4,
		NULL,
		GL_STATIC_DRAW
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		0,
		sizeof(vec4) * _floor.size,
		_floor.vertices
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _floor.size,
		sizeof(vec4) * _floor.size,
		_floor.colors
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _floor.size * 2,
		sizeof(vec4) * _floor.size,
		_floor.normals
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _floor.size * 3,
		sizeof(vec4) * _floor.size,
		_floor.textures
	);
}

// set up lines for axes
void axes(void) {
	_axes.size = 9;

	_axes.vertices = (vec4*)&axesVertices;
	_axes.colors = new vec4[_axes.size];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_axes.colors[i * 3 + j] = axesColors[i];
		}
	}

	glGenBuffers(1, &_axes.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _axes.buffer);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _axes.size * 4,
		NULL,
		GL_STATIC_DRAW
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		0,
		sizeof(vec4) * _axes.size,
		_axes.vertices
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _axes.size,
		sizeof(vec4) * _axes.size,
		_axes.colors
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _axes.size * 2,
		sizeof(vec4) * _axes.size,
		_axes.normals
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _axes.size * 3,
		sizeof(vec4) * _axes.size,
		_axes.textures
	);
}

// set up sphere
void sphere(void) {
	_sphere.size = sphereVertices.size();

	_sphere.vertices = &sphereVertices[0];
	_sphere.colors = new vec4[_sphere.size];

	sphereShadeFlat = new vec4[_sphere.size];
	sphereShadeSmooth = new vec4[_sphere.size];

	_sphere.normals = sphereShadeFlat;
	_sphere.textures = new vec2[_sphere.size];

	for (int i = 0; i < _sphere.size; i++) {
		_sphere.colors[i] = sphereColor;
	}

	for (int i = 0; i < _sphere.size; i += 3) {
		vec4 flatNormal = normalize(cross(
			_sphere.vertices[i + 1] - _sphere.vertices[i],
			_sphere.vertices[i + 2] - _sphere.vertices[i]
		));

		sphereShadeFlat[i] = flatNormal;
		sphereShadeFlat[i + 1] = flatNormal;
		sphereShadeFlat[i + 2] = flatNormal;

		sphereShadeSmooth[i] = normalize(_sphere.vertices[i]);;
		sphereShadeSmooth[i + 1] = normalize(_sphere.vertices[i + 1]);;
		sphereShadeSmooth[i + 2] = normalize(_sphere.vertices[i + 2]);;
	}


	vec4 y(0, 1, 0, 0);

	for (int i = 0; i < 3; i++) {
		sphereMovementVectors[i] = normalize(sphereMovementVertices[(i + 1) % 3] - sphereMovementVertices[i]);
		sphereRotationAxes[i] = cross(y, sphereMovementVectors[i]);
	}

	sphereCenter = sphereMovementVertices[sphereIndex];

	glGenBuffers(1, &_sphere.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _sphere.buffer);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _sphere.size * 4,
		NULL,
		GL_STATIC_DRAW
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		0,
		sizeof(vec4) * _sphere.size,
		_sphere.vertices
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _sphere.size,
		sizeof(vec4) * _sphere.size,
		_sphere.colors
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _sphere.size * 2,
		sizeof(vec4) * _sphere.size,
		_sphere.normals
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _sphere.size * 3,
		sizeof(vec4) * _sphere.size,
		_sphere.textures
	);
}

// set up shadow
void shadow(void) {
	_shadow.size = sphereVertices.size();

	_shadow.vertices = &sphereVertices[0];
	_shadow.colors = new vec4[_shadow.size];

	for (int i = 0; i < _shadow.size; i++) {
		_shadow.colors[i] = shadowColor;
	}

	glGenBuffers(1, &_shadow.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _shadow.buffer);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _shadow.size * 4,
		NULL,
		GL_STATIC_DRAW
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		0,
		sizeof(vec4) * _shadow.size,
		_shadow.vertices
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _shadow.size,
		sizeof(vec4) * _shadow.size,
		_shadow.colors
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _shadow.size * 2,
		sizeof(vec4) * _shadow.size,
		_shadow.normals
	);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(vec4) * _shadow.size * 3,
		sizeof(vec4) * _shadow.size,
		_shadow.textures
	);
}

// set up fog
void fog(void) {
	glUniform4fv(glGetUniformLocation(program, "fogColor"), 1, fogColor);
	glUniform1f(glGetUniformLocation(program, "fogStart"), (GLfloat)fogStart);
	glUniform1f(glGetUniformLocation(program, "fogEnd"), (GLfloat)fogEnd);
	glUniform1f(glGetUniformLocation(program, "fogDensity"), (GLfloat)fogDensity);
}

void message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	fprintf(
		stderr,
		"GL CALLBACK %s \n\ttype = 0x%x \n\tseverity = 0x%x \n\tmessage = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type,
		severity,
		message
	);
}

void init(void) {
	//glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback((GLDEBUGPROC)message, NULL);

	// initialize the shader
	program = InitShader("vshader53.glsl", "fshader53.glsl");

	texture();

	floor();

	axes();

	sphere();

	shadow();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(2.0);
}

void light(mat4 mv, const Light& global, const Light& dLight, const Light& pLight, const Light& material) {
	glUniform1f(glGetUniformLocation(program, "shininess"), material.shininess);

	// global
	glUniform4fv(glGetUniformLocation(program, "globalLight"), 1, global.ambient * material.ambient);

	// directional
	glUniform4fv(glGetUniformLocation(program, "dPosition"), 1, dLight.position);
	glUniform4fv(glGetUniformLocation(program, "dDirection"), 1, dLight.direction);

	glUniform4fv(glGetUniformLocation(program, "dAmbientProduct"), 1, dLight.ambient * material.ambient);
	glUniform4fv(glGetUniformLocation(program, "dDiffuseProduct"), 1, dLight.diffuse * material.diffuse);
	glUniform4fv(glGetUniformLocation(program, "dSpecularProduct"), 1, dLight.specular * material.specular);

	glUniform1f(glGetUniformLocation(program, "dConstAtt"), dLight.attenuationConstant);
	glUniform1f(glGetUniformLocation(program, "dLinearAtt"), dLight.attenuationLinear);
	glUniform1f(glGetUniformLocation(program, "dQuadAtt"), dLight.attenuationQuadratic);

	// positional
	glUniform4fv(glGetUniformLocation(program, "pPosition"), 1, mv * pLight.position);
	glUniform4fv(glGetUniformLocation(program, "pDirection"), 1, mv * pLight.direction);

	glUniform4fv(glGetUniformLocation(program, "pAmbientProduct"), 1, pLight.ambient * material.ambient);
	glUniform4fv(glGetUniformLocation(program, "pDiffuseProduct"), 1, pLight.diffuse * material.diffuse);
	glUniform4fv(glGetUniformLocation(program, "pSpecularProduct"), 1, pLight.specular * material.specular);

	glUniform1f(glGetUniformLocation(program, "pConstAtt"), pLight.attenuationConstant);
	glUniform1f(glGetUniformLocation(program, "pLinearAtt"), pLight.attenuationLinear);
	glUniform1f(glGetUniformLocation(program, "pQuadAtt"), pLight.attenuationQuadratic);

	glUniform1f(glGetUniformLocation(program, "pExponent"), pLight.exponent);
	glUniform1f(glGetUniformLocation(program, "pAngle"), cos(pLight.angle * (M_PI / 180)));
}

void flags(void) {
	glUniform1i(glGetUniformLocation(program, "flagShadow"), flagShadow);
	glUniform1i(glGetUniformLocation(program, "flagShading"), flagShading);
	glUniform1i(glGetUniformLocation(program, "flagWire"), flagWire);
	glUniform1i(glGetUniformLocation(program, "flagLight"), flagLight);
	glUniform1i(glGetUniformLocation(program, "flagLightType"), flagLightType);
	glUniform1i(glGetUniformLocation(program, "flagFogType"), flagFogType);
	glUniform1i(glGetUniformLocation(program, "flagShadowBlend"), flagShadowBlend);
	glUniform1i(glGetUniformLocation(program, "flagFrame"), flagFrame);
	glUniform1i(glGetUniformLocation(program, "flagTextureOrientation"), flagTextureOrientation);

	glUniform1i(glGetUniformLocation(program, "texture2d"), GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "texture1d"), GL_TEXTURE1);
}

void display(void) {
	flags();

	// set to true only when drawing the respective objects
	glUniform1i(glGetUniformLocation(program, "flagFloorTexture"), false);
	glUniform1i(glGetUniformLocation(program, "flagSphereTexture"), false);

	// pass on eye
	glUniform4fv(glGetUniformLocation(program, "eye"), 1, eye);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// background
	glClearColor(0.529, 0.807, 0.92, 1);

	glUseProgram(program);

	GLuint modelView = glGetUniformLocation(program, "modelView");
	GLuint projection = glGetUniformLocation(program, "projection");
	GLuint normalMatrix = glGetUniformLocation(program, "normalMatrix");

	// set up model view matrix
	// VRP (view reference vertices)
	// eye is global

	// VPN (view plane normal) -7, -3, 10, 0;
	vec4 at(0, 0, 0, 1);

	// VUP (view up vector)
	vec4 up(0, 1, 0, 0);

	mat4 mv = LookAt(eye, at, up);
	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);

	mat3 nm = NormalMatrix(mv, 1);
	glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, nm);

	// set up projection matrix
	GLfloat fovy = 45;
	GLfloat zNear = 0.5;
	GLfloat zFar = 13;

	mat4 p = Perspective(fovy, aspect, zNear, zFar);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);

	// set up fog
	fog();

	// draw axes lines
	glUniform1i(glGetUniformLocation(program, "flagLight"), false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawObject(_axes.buffer, _axes.size, program);
	glUniform1i(glGetUniformLocation(program, "flagLight"), flagLight);

	// draw sphere
	glUniform1i(glGetUniformLocation(program, "flagSphereTexture"), true);
	sphereRotationMatrix = Rotate(
		sphereRate,
		sphereRotationAxes[sphereIndex].x,
		sphereRotationAxes[sphereIndex].y,
		sphereRotationAxes[sphereIndex].z
	) * sphereRotationMatrix;
	mv *= Translate(sphereCenter.x, sphereCenter.y, sphereCenter.z) * sphereRotationMatrix;
	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);
	glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, NormalMatrix(mv, 1));
	if (flagLightType) {
		light(mv, ambientLight, directionalLight, pointLight, sphereLight);
	} else {
		light(mv, ambientLight, directionalLight, spotLight, sphereLight);
	}
	if (flagWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform1i(glGetUniformLocation(program, "flagLight"), false);
		drawObject(_sphere.buffer, _sphere.size, program);
		glUniform1i(glGetUniformLocation(program, "flagLight"), flagLight);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		drawObject(_sphere.buffer, _sphere.size, program);
	}
	glUniform1i(glGetUniformLocation(program, "flagSphereTexture"), false);

	mv = LookAt(eye, at, up);
	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);
	nm = NormalMatrix(mv, 1);
	glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, nm);

	// draw floor and shadow only to frame buffer
	glDepthMask(GL_FALSE);

	if (flagLightType) {
		light(mv, ambientLight, directionalLight, pointLight, floorLight);
	} else {
		light(mv, ambientLight, directionalLight, spotLight, floorLight);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform1i(glGetUniformLocation(program, "flagFloorTexture"), flagFloorTexture);
	drawObject(_floor.buffer, _floor.size, program);
	glUniform1i(glGetUniformLocation(program, "flagFloorTexture"), false);

	// draw shadow
	if (flagShadow) {
		glUniform1i(glGetUniformLocation(program, "flagLight"), false);
		mat4 shadowMatrix(
			vec4(1, 0, 0, 0),
			vec4(0, 1, 0, 0),
			vec4(0, 0, 1, 0),
			vec4(0, -1 / spotLight.position.y, 0, 0)
		);
		mv = LookAt(eye, at, up) * Translate(spotLight.position) * shadowMatrix * Translate(-spotLight.position) * Translate(sphereCenter.x, sphereCenter.y, sphereCenter.z) * sphereRotationMatrix;
		glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);
		nm = NormalMatrix(mv, 1);
		glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, nm);

		if (flagWire) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (flagShadowBlend) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			drawObject(_shadow.buffer, _shadow.size, program);
			glDisable(GL_BLEND);
		} else {
			drawObject(_shadow.buffer, _shadow.size, program);
		}

		glUniform1i(glGetUniformLocation(program, "flagLight"), flagLight);
	}

	glDepthMask(GL_TRUE);

	// draw floor only to z buffer
	mv = LookAt(eye, at, up);
	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);
	nm = NormalMatrix(mv, 1);
	glUniformMatrix3fv(normalMatrix, 1, GL_TRUE, nm);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	if (flagLightType) {
		light(mv, ambientLight, directionalLight, pointLight, floorLight);
	} else {
		light(mv, ambientLight, directionalLight, spotLight, floorLight);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform1i(glGetUniformLocation(program, "flagFloorTexture"), flagFloorTexture);
	drawObject(_floor.buffer, _floor.size, program);
	glUniform1i(glGetUniformLocation(program, "flagFloorTexture"), false);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glutSwapBuffers();
}

void idle(void) {
	float offset = sphereRadius * sphereRate * (M_PI / 180);

	sphereCenter.x += sphereMovementVectors[sphereIndex].x * offset;
	sphereCenter.y += sphereMovementVectors[sphereIndex].y * offset;
	sphereCenter.z += sphereMovementVectors[sphereIndex].z * offset;

	// check for when the sphere should turn
	if (distance(sphereCenter, sphereMovementVertices[sphereIndex]) >= distance(sphereMovementVertices[(sphereIndex + 1) % 3], sphereMovementVertices[sphereIndex])) {
		sphereIndex = (sphereIndex + 1) % 3;
		sphereCenter = sphereMovementVertices[sphereIndex];
	}

	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	aspect = (GLfloat) w / (GLfloat) h;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 033: // Escape Key
		case 'q': case 'Q':
			exit(EXIT_SUCCESS);
			break;

		case 'X':
			eye[0] += 1.0;
			break;

		case 'x':
			eye[0] -= 1.0;
			break;

		case 'Y':
			eye[1] += 1.0;
			break;

		case 'y':
			eye[1] -= 1.0;
			break;

		case 'Z':
			eye[2] += 1.0;
			break;

		case 'z':
			eye[2] -= 1.0;
			break;

		case 'v':
		case 'V':
			flagTextureOrientation = false;
			break;

		case 's':
		case 'S':
			flagTextureOrientation = true;
			break;

		case 'o':
		case 'O':
			flagFrame = false;
			break;

		case 'e':
		case 'E':
			flagFrame = true;
			break;

		case 'b':
		case 'B':
			flagStarted = true;
			flagAnimation = !flagAnimation;

			if (flagAnimation) {
				glutIdleFunc(idle);
			} else {
				glutIdleFunc(NULL);
			}
			break;

		case ' ':
			eye = originalEye;
			break;
	}

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP && flagStarted) {
		flagAnimation = !flagAnimation;
	}

	if (flagAnimation) {
		glutIdleFunc(idle);
	} else {
		glutIdleFunc(NULL);
	}
}

void menu(int index) {
	switch (index) {
		case 0:
			flagShadow = false;
			break;

		case 1:
			flagShadow = true;
			break;

		case 2:
			flagShadowBlend = false;
			break;

		case 3:
			flagShadowBlend = true;
			break;

		case 4:
			flagLight = false;
			glUniform1i(glGetUniformLocation(program, "flagLight"), flagLight);
			break;

		case 5:
			flagLight = true;
			glUniform1i(glGetUniformLocation(program, "flagLight"), flagLight);
			break;

		case 6:
			flagShading = false;
			_sphere.normals = sphereShadeFlat;
			glUniform1i(glGetUniformLocation(program, "flagShading"), flagShading);
			glBindBuffer(GL_ARRAY_BUFFER, _sphere.buffer);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * _sphere.size * 2, sizeof(vec4) * _sphere.size, _sphere.normals);
			break;

		case 7:
			flagShading = true;
			_sphere.normals = sphereShadeSmooth;
			glUniform1i(glGetUniformLocation(program, "flagShading"), flagShading);
			glBindBuffer(GL_ARRAY_BUFFER, _sphere.buffer);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4) * _sphere.size * 2, sizeof(vec4) * _sphere.size, _sphere.normals);
			break;

		case 8:
			flagLightType = false;
			glUniform1i(glGetUniformLocation(program, "flagLightType"), flagLightType);
			break;

		case 9:
			flagLightType = true;
			glUniform1i(glGetUniformLocation(program, "flagLightType"), flagLightType);
			break;

		case 10:
			// none
			flagFogType = 0;
			glUniform1i(glGetUniformLocation(program, "flagFogType"), flagFogType);
			break;

		case 11:
			// linear
			flagFogType = 1;
			glUniform1i(glGetUniformLocation(program, "flagFogType"), flagFogType);
			break;

		case 12:
			// exponential
			flagFogType = 2;
			glUniform1i(glGetUniformLocation(program, "flagFogType"), flagFogType);
			break;

		case 13:
			// exponential square
			flagFogType = 3;
			glUniform1i(glGetUniformLocation(program, "flagFogType"), flagFogType);
			break;

		case 14:
			flagFloorTexture = false;
			glUniform1i(glGetUniformLocation(program, "flagFloorTexture"), flagFloorTexture);
			break;

		case 15:
			flagFloorTexture = true;
			glUniform1i(glGetUniformLocation(program, "flagFloorTexture"), flagFloorTexture);
			break;

		case 16:
			eye = originalEye;
			break;

		case 17:
			flagWire = !flagWire;
			break;

		case 18:
			exit(EXIT_SUCCESS);
			break;
	}

	display();
}

int main(int argc, char** argv) {
	readFile("sphere.256", "sphere.1024", sphereVertices, shadowVertices);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Rotating Sphere");

	// Call glewInit() and error checking
	int err = glewInit();
	if (GLEW_OK != err) {
		printf("Error: glewInit failed: %s\n", (char*) glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	GLuint shadowMenu = glutCreateMenu(menu);
	glutAddMenuEntry("No", 0);
	glutAddMenuEntry("Yes", 1);

	GLuint shadowBlendingMenu = glutCreateMenu(menu);
	glutAddMenuEntry("No", 2);
	glutAddMenuEntry("Yes", 3);

	GLuint lightingMenu = glutCreateMenu(menu);
	glutAddMenuEntry("No", 4);
	glutAddMenuEntry("Yes", 5);

	GLuint shadingMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Flat Shading", 6);
	glutAddMenuEntry("Smooth Shading", 7);

	GLuint lightTypeMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Spot Light", 8);
	glutAddMenuEntry("Point Source", 9);

	GLuint fogTypeMenu = glutCreateMenu(menu);
	glutAddMenuEntry("No Fog", 10);
	glutAddMenuEntry("Linear Fog", 11);
	glutAddMenuEntry("Exponential Fog", 12);
	glutAddMenuEntry("Exponential Square Fog", 13);

	GLuint floorTextureMenu = glutCreateMenu(menu);
	glutAddMenuEntry("No", 14);
	glutAddMenuEntry("Yes", 15);

	glutCreateMenu(menu);
	glutAddMenuEntry("Default View Point", 16);
	glutAddMenuEntry("Wire Frame Sphere", 17);
	glutAddSubMenu("Shadow", shadowMenu);
	glutAddSubMenu("Blending Shadow", shadowBlendingMenu);
	glutAddSubMenu("Enable Lighting", lightingMenu);
	glutAddSubMenu("Shading", shadingMenu);
	glutAddSubMenu("Light Source", lightTypeMenu);
	glutAddSubMenu("Fog", fogTypeMenu);
	glutAddSubMenu("Texture Mapped Ground", floorTextureMenu);
	glutAddMenuEntry("Quit", 18);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutDisplayFunc(display);
	glutIdleFunc(NULL);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	init();
	glutMainLoop();

	return EXIT_SUCCESS;
}
