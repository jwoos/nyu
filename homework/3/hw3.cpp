#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Angel-yjc.h"
#include "utils.h"
#include "globals.h"


using namespace std;


extern bool flagAnimation;
extern bool flagStarted;

extern GLuint program;
extern GLuint programLight;

extern vec4 originalEye;
extern vec4 eye;
extern GLuint aspect;

extern Entity _floor;
extern vec3 floorColor;
extern vec3 floorVertices[4];

extern Entity _axes;
extern vec3 axesColors[3];
extern vec3 axesVertices[9];

extern Entity _sphere;
extern vec3 sphereColor;
extern vector<vec3> sphereVertices;

extern vec3 sphereMovementVertices[3];
extern vec3 sphereMovementVectors[3];
extern vec3 sphereRotationAxes[3];
extern vec3 sphereCenter;
extern int sphereIndex;
extern float sphereRadius;
extern float sphereRate;
extern mat4 sphereRotationMatrix;

extern Entity _shadow;
extern vec3 shadowColor;
extern vector<vec3> shadowVertices;

extern vec4 lightPosition;


void menu(int index) {
	switch (index) {
		case 0:
			eye = originalEye;
			break;

		case 1:
			exit(EXIT_SUCCESS);
			break;
	}
}

// set up floor
void floor(void) {
	_floor.size = 6;
	_floor.vertices = new vec3[_floor.size];
	_floor.colors = new vec3[_floor.size];

	_floor.vertices[0] = floorVertices[0];
	_floor.vertices[1] = floorVertices[1];
	_floor.vertices[2] = floorVertices[2];
	_floor.vertices[3] = floorVertices[0];
	_floor.vertices[4] = floorVertices[2];
	_floor.vertices[5] = floorVertices[3];

	for (int i = 0; i < _floor.size; i++) {
		_floor.colors[i] = floorColor;
	}

	glGenBuffers(1, &_floor.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _floor.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _floor.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _floor.size, _floor.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _floor.size, sizeof(vec3) * _floor.size, _floor.colors);
}

// set up lines for axes
void axes(void) {
	_axes.size = 9;

	_axes.vertices = (vec3*)&axesVertices;
	_axes.colors = new vec3[_axes.size];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_axes.colors[i * 3 + j] = axesColors[i];
		}
	}

	glGenBuffers(1, &_axes.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _axes.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _axes.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _axes.size, _axes.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _axes.size, sizeof(vec3) * _axes.size, _axes.colors);
}

// set up sphere
void sphere(void) {
	_sphere.size = sphereVertices.size();

	_sphere.vertices = &sphereVertices[0];
	_sphere.colors = new vec3[_sphere.size];

	for (int i = 0; i < _sphere.size; i++) {
		_sphere.colors[i] = sphereColor;
	}

	vec3 y(0, 1, 0);

	for (int i = 0; i < 3; i++) {
		sphereMovementVectors[i] = normalize(sphereMovementVertices[(i + 1) % 3] - sphereMovementVertices[i]);
		sphereRotationAxes[i] = cross(y, sphereMovementVectors[i]);
	}

	sphereCenter = sphereMovementVertices[sphereIndex];

	glGenBuffers(1, &_sphere.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _sphere.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _sphere.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _sphere.size, _sphere.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _sphere.size, sizeof(vec3) * _sphere.size, _sphere.colors);
}

// set up shadow
void shadow(void) {
	_shadow.size = sphereVertices.size();

	_shadow.vertices = &sphereVertices[0];
	_shadow.colors = new vec3[_shadow.size];

	for (int i = 0; i < _shadow.size; i++) {
		_shadow.colors[i] = shadowColor;
	}

	glGenBuffers(1, &_shadow.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _shadow.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _shadow.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _shadow.size, _shadow.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _shadow.size, sizeof(vec3) * _shadow.size, _shadow.colors);
}

void init(void) {
	floor();

	axes();

	sphere();

	shadow();

	// initialize the shader
	program = InitShader("vshader42.glsl", "fshader42.glsl");
	programLight = InitShader("vshader53.glsl", "fshader53.glsl");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(2.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// background
	glClearColor(0.529, 0.807, 0.92, 1);

	glUseProgram(program);

	GLuint modelView = glGetUniformLocation(program, "modelView");
	GLuint projection = glGetUniformLocation(program, "projection");

	// set up model view matrix
	// VRP (view reference vertices)
	// eye is global

	// VPN (view plane normal) -7, -3, 10, 0;
	vec4 at(0, 0, 0, 1);

	// VUP (view up vector)
	vec4 up(0, 1, 0, 0);

	mat4 mv = LookAt(eye, at, up);
	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);

	// set up projection matrix
	GLfloat fovy = 45;
	GLfloat zNear = 0.5;
	GLfloat zFar = 13;

	mat4 p = Perspective(fovy, aspect, zNear, zFar);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);

	// draw floor
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawObj(_floor.buffer, _floor.size, program);

	// draw axes lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawObj(_axes.buffer, _axes.size, program);

	// draw sphere
	sphereRotationMatrix = Rotate(
		sphereRate,
		sphereRotationAxes[sphereIndex].x,
		sphereRotationAxes[sphereIndex].y,
		sphereRotationAxes[sphereIndex].z
	) * sphereRotationMatrix;
	// the rightmost rotations ones are applied first
	mv *= Translate(sphereCenter.x, sphereCenter.y, sphereCenter.z) * sphereRotationMatrix;
	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawObj(_sphere.buffer, _sphere.size, program);

	// draw shadow
	// FIXME get the correct shadow matrix
	mv = LookAt(eye, at, up) *  mat4(12, 0, 0, 0, 14, 0, 3, -1, 0, 0, 12, 0, 0, 0, 0, 12) * Translate(sphereCenter.x, sphereCenter.y, sphereCenter.z) * sphereRotationMatrix;
	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawObj(_shadow.buffer, _shadow.size, program);

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

	glutCreateMenu(menu);
	glutAddMenuEntry("Default View Point", 0);
	glutAddMenuEntry("Quit", 1);
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
