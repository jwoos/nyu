#include "utils.h"


void drawObject(GLuint buffer, int vertexCount, GLuint program) {
	//--- Activate the vertex buffer object to be drawn ---//
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	/*----- Set up vertex attribute arrays for each vertex attribute -----*/
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4) * vertexCount));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4) * vertexCount * 2));

	GLuint vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4) * vertexCount * 3));

	/* Draw a sequence of geometric objs (triangles) from the vertex buffer
	   (using the attributes specified in each enabled vertex attribute array) */
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	/*--- Disable each vertex attribute array being enabled ---*/
	glDisableVertexAttribArray(vPosition);
	glDisableVertexAttribArray(vColor);
	glDisableVertexAttribArray(vNormal);
	glDisableVertexAttribArray(vTexture);
}

void drawParticles(GLuint buffer, int vertexCount, GLuint program) {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vVelocity = glGetAttribLocation(program, "vVelocity");
	glEnableVertexAttribArray(vVelocity);
	glVertexAttribPointer(vVelocity, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec4) * vertexCount));

	glDrawArrays(GL_POINTS, 0, vertexCount);

	glDisableVertexAttribArray(vColor);
	glDisableVertexAttribArray(vVelocity);
}

// reads in points into spherePoints
void readFile(const string& a, const string& b, vector<vec4>& spherePoints, vector<vec4>& shadowPoints) {
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

			spherePoints.push_back(vec4(x, y, z, 1));
			shadowPoints.push_back(vec4(x, y, z, 1));
		}
	}

	file.close();
}

// distance between two points
float distance(const vec4& a, const vec4& b) {
	vec4 dist = a - b;
	return sqrt(dot(dist, dist));
}
