#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Angel-yjc.h"


using namespace std;


typedef struct Entity {
	vec3* points;
	vec3* colors;

	GLuint buffer;

	int size;
} Entity;


GLuint program;

vector<vec3> spherePoints;

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

Entity _axis;

Entity _sphere;

void readFile() {
	string filename;

	cout << "Enter the file to read" << endl;
	cin >> filename;

	ifstream file;
	file.open(filename);

	if (!file) {
		cerr << "Unable to open file" << endl;
		exit(EXIT_FAILURE);
	}

	int n;
	file >> n;

	for (int i = 0; i < n; i++) {
		int points;

		float x;
		float y;
		float z;

		file >> points;

		for (int j = 0; j < points; j++) {
			file >> x >> y >> z;

			spherePoints.push_back(vec3(x, y, z));
		}
	}

	file.close();
}

void drawObj(GLuint buffer, int num_vertices) {
	//--- Activate the vertex buffer object to be drawn ---//
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	/*----- Set up vertex attribute arrays for each vertex attribute -----*/
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec3) * num_vertices));
	// the offset is the (total) size of the previous vertex attribute array(s)

	/* Draw a sequence of geometric objs (triangles) from the vertex buffer
	   (using the attributes specified in each enabled vertex attribute array) */
	glDrawArrays(GL_TRIANGLES, 0, num_vertices);

	/*--- Disable each vertex attribute array being enabled ---*/
	glDisableVertexAttribArray(vPosition);
	glDisableVertexAttribArray(vColor);
}

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
}

void axis(void) {
	_axis.size = 9;

	_axis.points = new vec3[_axis.size];
	_axis.colors = new vec3[_axis.size];

	_axis.points[0] = vec3(0, 0, 0);
	_axis.points[1] = vec3(10, 0, 0);
	_axis.points[2] = vec3(20, 0, 0);

	_axis.points[3] = vec3(0, 0, 0);
	_axis.points[4] = vec3(0, 10, 0);
	_axis.points[5] = vec3(0, 20, 0);

	_axis.points[6] = vec3(0, 0, 0);
	_axis.points[7] = vec3(0, 0, 10);
	_axis.points[8] = vec3(0, 0, 20);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_axis.colors[i + j] = axisColors[i];
		}
	}
}

void sphere(void) {
	_sphere.size = spherePoints.size();

	_sphere.points = &spherePoints[0];
	_sphere.colors = new vec3[_sphere.size];

	for (int i = 0; i < _sphere.size; i++) {
		_sphere.colors[i] = colorSphere;
	}
}

void init(void) {
	floor();
	glGenBuffers(1, &_floor.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _floor.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _floor.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _floor.size, _floor.points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _floor.size, sizeof(vec3) * _floor.size, _floor.colors);

	axis();
	glGenBuffers(1, &_axis.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _axis.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _axis.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _axis.size, _axis.points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _axis.size, sizeof(vec3) * _axis.size, _axis.colors);

	sphere();
	glGenBuffers(1, &_sphere.buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _sphere.buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _sphere.size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * _sphere.size, _sphere.points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * _sphere.size, sizeof(vec3) * _sphere.size, _sphere.colors);

	// initialize the shader
	program = InitShader("vshader.glsl", "fshader.glsl");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(2.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// background
	glClearColor(0.529, 0.807, 0.92, 1);

	glUseProgram(program);

	GLuint model_view = glGetUniformLocation(program, "model_view");
	GLuint projection = glGetUniformLocation(program, "projection");

	// set up model view matrix
	// VRP (view reference points)
	vec4 eye(7, 3, -10, 1);

	// VPN (view plane normal) -7, -3, 10, 0;
	vec4 at(0, 0, 0, 1);

	// VUP (view up vector)
	vec4 up(0, 1, 0, 0);

	mat4 mv = LookAt(eye, at, up);
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	// set up projection matrix
	GLfloat fovy = 45;
	GLfloat zNear = 0.5;
	GLfloat zFar = 13;

	mat4 p = Perspective(fovy, aspect, zNear, zFar);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);

	// draw floor
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawObj(_floor.buffer, _floor.size);

	// draw axis lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawObj(_axis.buffer, _axis.size);

	// draw sphere
	mv *= Translate(-4, 1, 4);
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawObj(_sphere.buffer, _sphere.size);

	glutSwapBuffers();
}

void idle(void) {
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	aspect = (GLfloat) w / (GLfloat) h;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

}

int main(int argc, char** argv) {
	readFile();

	for (vector<vec3>::iterator it = spherePoints.begin(); it != spherePoints.end(); it++) {
		cout << (*it).x << " " << (*it).y << " " << (*it).z << endl;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Rotating Sphere");

	/* Call glewInit() and error checking */
	int err = glewInit();
	if (GLEW_OK != err) {
		printf("Error: glewInit failed: %s\n", (char*) glewGetErrorString(err));
		exit(1);
	}

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	init();
	glutMainLoop();

	return 0;
}
