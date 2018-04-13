#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Angel-yjc.h"
#include "utils.h"
#include "globals.h"


using namespace std;


extern GLuint program;
extern vec4 originalEye;
extern vec4 eye;
extern bool animation;
extern bool started;
extern GLuint aspect;

extern vec3 colorSphere;
extern vec3 colorFloor;
extern vec3 axisColors[3];

extern vec3 floorVertices[4];

extern Entity _floor;

extern Entity _axes;

extern vec3 pathPoints[3];
extern vector<vec3> spherePoints;
extern vec3 movementVectors[3];
extern vec3 rotationAxes[3];
extern vec3 sphereCenter;
extern int sphereIndex;
extern float radius;
extern float angle;
extern float rate;
extern mat4 rotationMatrix;
extern Entity _sphere;

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
	_floor.points = new vec3[_floor.size];
	_floor.colors = new vec3[_floor.size];

	_floor.points[0] = floorVertices[0];
	_floor.points[1] = floorVertices[1];
	_floor.points[2] = floorVertices[2];
	_floor.points[3] = floorVertices[0];
	_floor.points[4] = floorVertices[2];
	_floor.points[5] = floorVertices[3];

	for (int i = 0; i < _floor.size; i++) {
		_floor.colors[i] = colorFloor;
	}

	glGenBuffers(1, &_floor.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _floor.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _floor.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _floor.size, _floor.points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _floor.size, sizeof(vec3) * _floor.size, _floor.colors);
}

// set up lines for axes
void axes(void) {
	_axes.size = 9;

	_axes.points = new vec3[_axes.size];
	_axes.colors = new vec3[_axes.size];

	_axes.points[0] = vec3(0, 0, 0);
	_axes.points[1] = vec3(10, 0, 0);
	_axes.points[2] = vec3(20, 0, 0);

	_axes.points[3] = vec3(0, 0, 0);
	_axes.points[4] = vec3(0, 10, 0);
	_axes.points[5] = vec3(0, 20, 0);

	_axes.points[6] = vec3(0, 0, 0);
	_axes.points[7] = vec3(0, 0, 10);
	_axes.points[8] = vec3(0, 0, 20);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_axes.colors[i * 3 + j] = axisColors[i];
		}
	}

	glGenBuffers(1, &_axes.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _axes.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _axes.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _axes.size, _axes.points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _axes.size, sizeof(vec3) * _axes.size, _axes.colors);
}

// set up sphere
void sphere(void) {
	_sphere.size = spherePoints.size();

	_sphere.points = &spherePoints[0];
	_sphere.colors = new vec3[_sphere.size];

	for (int i = 0; i < _sphere.size; i++) {
		_sphere.colors[i] = colorSphere;
	}

	vec3 y(0, 1, 0);

	for (int i = 0; i < 3; i++) {
		movementVectors[i] = normalize(pathPoints[(i + 1) % 3] - pathPoints[i]);
		rotationAxes[i] = cross(y, movementVectors[i]);
	}

	sphereCenter = pathPoints[sphereIndex];

	glGenBuffers(1, &_sphere.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _sphere.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _sphere.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _sphere.size, _sphere.points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _sphere.size, sizeof(vec3) * _sphere.size, _sphere.colors);
}

void init(void) {
	floor();

	axes();

	sphere();

	// initialize the shader
	program = InitShader("vshader42.glsl", "fshader42.glsl");

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
	// VRP (view reference points)
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
	// the rightmost rotations ones are applied first
	rotationMatrix = Rotate(rate, rotationAxes[sphereIndex].x, rotationAxes[sphereIndex].y, rotationAxes[sphereIndex].z) * rotationMatrix;
	mv *= Translate(sphereCenter.x, sphereCenter.y, sphereCenter.z) * rotationMatrix;

	glUniformMatrix4fv(modelView, 1, GL_TRUE, mv);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawObj(_sphere.buffer, _sphere.size, program);

	glutSwapBuffers();
}

void idle(void) {
	angle += rate;

	if (angle >= 360) {
		angle = 0;
	}

	float offset = radius * rate * (M_PI / 180);

	sphereCenter.x += movementVectors[sphereIndex].x * offset;
	sphereCenter.y += movementVectors[sphereIndex].y * offset;
	sphereCenter.z += movementVectors[sphereIndex].z * offset;

	// check for when the sphere should turn
	if (distance(sphereCenter, pathPoints[sphereIndex]) >= distance(pathPoints[(sphereIndex + 1) % 3], pathPoints[sphereIndex])) {
		sphereIndex = (sphereIndex + 1) % 3;
		sphereCenter = pathPoints[sphereIndex];
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
			started = true;
			animation = !animation;

			if (animation) {
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
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP && started) {
		animation = !animation;
	}

	if (animation) {
		glutIdleFunc(idle);
	} else {
		glutIdleFunc(NULL);
	}
}

int main(int argc, char** argv) {
	readFile("sphere.256", "sphere.1024", spherePoints);

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
