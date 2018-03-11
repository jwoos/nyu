#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Angel-yjc.h"


using namespace std;


void readFile(vector<vector<vec3>>& spherePoints) {
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
		vector<vec3> temp;
		int points;

		float x;
		float y;
		float z;

		file >> points;

		for (int j = 0; j < points; j++) {
			file >> x >> y >> z;

			temp.push_back(vec3(x, y, z));
		}

		spherePoints.push_back(temp);
	}

	file.close();
}

void init(void) {

}

void display(void) {

}

void idle(void) {

}

void reshape(int w, int h) {

}

void keyboard(char key, int x, int y) {

}

int main(int argc, char** argv) {
	vector<vector<vec3>> spherePoints;

	readFile(spherePoints);

	for (vector<vector<vec3>>::iterator it = spherePoints.begin(); it != spherePoints.end(); it++) {
		for (vector<vec3>::iterator jt = (*it).begin(); jt != (*it).end(); jt++) {
			cout << (*jt).x << " " << (*jt).y << " " << (*jt).z << endl;
		}
	}

/*
 *    glutInit(&argc, argv);
 *    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
 *    glutInitWindowSize(512, 512);
 *    glutCreateWindow("Rotating Sphere");
 *
 *    [> Call glewInit() and error checking <]
 *    int err = glewInit();
 *    if (GLEW_OK != err) {
 *        printf("Error: glewInit failed: %s\n", (char*) glewGetErrorString(err));
 *        exit(1);
 *    }
 *
 *    // Get info of GPU and supported OpenGL version
 *    printf("Renderer: %s\n", glGetString(GL_RENDERER));
 *    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
 *
 *    glutDisplayFunc(display);
 *    glutIdleFunc(idle);
 *    glutReshapeFunc(reshape);
 *    glutKeyboardFunc(keyboard);
 *
 *    init();
 *
 *    glutMainLoop();
 */

	return 0;
}
