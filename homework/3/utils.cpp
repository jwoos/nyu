#include "utils.h"


void drawObj(GLuint buffer, int num_vertices, GLuint program) {
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

// reads in points into spherePoints
void readFile(const string& a, const string& b, vector<vec3>& spherePoints) {
	string filename;

	cout << "Enter the file to read - 1 is shortcut for ";
	cout << a;
	cout << " and 2 is shortcut for ";
	cout << b << endl;

	cin >> filename;

	if (filename == "1") {
		filename = a;
	} else if (filename == "2") {
		filename = b;
	}

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

// distance between two points
float distance(const vec3& a, const vec3& b) {
	vec3 dist = a - b;
	return sqrt(dot(dist, dist));
}
