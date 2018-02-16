#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// #include <GL/glew.h>   // We don't need the GLEW library for now
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#define XOFF          50
#define YOFF          50
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600


void draw_circle(int, int, int);

void file_in(void);

void display(void (*fn)(void));

void myinit(void);

void scaleFactor(int, int, int, float*);

void scaleFactors(int**, float*);

void c(void);

void displayC(void);

void d(void);

void displayD(void);

void e(void);

void displayE(void);


// part c vars
int c_x;
int c_y;
int c_r;

// part d/e vars
int** coords;

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	/* Use both double buffering and Z buffer */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(XOFF, YOFF);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CS6533/CS4533 Assignment 1");

	bool invalid = true;
	void (*fn)(void);
	while (invalid) {
		printf("Specify which part to run (c | d | e): ");
		char command = getchar();
		switch (command) {
			case 'c':
				fn = displayC;
				invalid = false;
				printf("Enter the cx, cy and r separated by spaces: ");
				scanf("%d %d %d", &c_x, &c_y, &c_r);
				break;
			case 'd':
				fn = displayD;
				invalid = false;
				break;
			case 'e':
				fn = displayE;
				invalid = false;
				break;

			default:
				printf("Please enter a valid command\n");
				break;
		}
	}


	/* Function call to handle file input here */
	file_in();

	glutDisplayFunc(fn);

	myinit();
	glutMainLoop();

	return 0;
}


void draw_circle(int x, int y, int r) {
	int currentX = r;
	int currentY = 0;
	int shiftedX = x;
	int shiftedXn = -x;
	int shiftedY = y;
	int shiftedYn = -y;
	int shiftedXi = y;
	int shiftedXni = -y;
	int shiftedYi = x;
	int shiftedYni = -x;
	int d = 0;
	int r2 = r * r;

	while (currentX >= currentY) {
		// first try
		if (!d) {
			d = 4 * (currentX * currentX) - 4 * currentX + 1 + 4 * (currentY * currentY) + 8 * currentY + 4 - 4 * r2;
		} else {
			if (d < 0) {
				// N
				d = d + 8 * currentY + 12;
			} else {
				// NW
				d = d + 8 * (currentY - currentX) + 20;
				currentX--;
			}
		}

		// shift by x and y to draw a circle that is not centered on origin
		shiftedX = currentX + x;
		shiftedXn = -currentX + x;
		shiftedY = currentY + y;
		shiftedYn = -currentY + y;

		glVertex2i(shiftedX, shiftedY);
		glVertex2i(shiftedXn, shiftedY);
		glVertex2i(shiftedX, shiftedYn);
		glVertex2i(shiftedXn, shiftedYn);

		/* can't just switch x and y since that's a flip over x=y
		 * so instead use the y and add the x offset and use x and
		 * add y offset
		 */
		shiftedXi = currentY + x;
		shiftedXni = -currentY + x;
		shiftedYi = currentX + y;
		shiftedYni = -currentX + y;

		glVertex2i(shiftedXi, shiftedYi);
		glVertex2i(shiftedXni, shiftedYi);
		glVertex2i(shiftedXi, shiftedYni);
		glVertex2i(shiftedXni, shiftedYni);

		currentY++;
	}
}

void file_in(void) {
	char* filename = "../input_circles.txt";
	FILE* f = fopen(filename, "r");
	if (!f) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	char buffer[100];
	char* endPointer;
	// get first number
	fgets(buffer, 100, f);
	int num = strtol(buffer, NULL, 10);
	int* numBuffer;
	coords = calloc(num + 1, sizeof(int*));

	if (coords == NULL) {
		perror("calloc failure");
		exit(EXIT_FAILURE);
	}
	coords[num] = NULL;

	for (int i = 0; i < num; i++) {
		numBuffer = calloc(3, sizeof(int));
		if (numBuffer == NULL) {
			perror("calloc failure");
			exit(EXIT_FAILURE);
		}

		fgets(buffer, 100, f);
		endPointer = buffer;
		int index = 0;

		char* curr = buffer;
		do {
			if (index != 0) {
				endPointer++;
			}
			numBuffer[index] = strtol(endPointer, &endPointer, 10);
			index++;
		} while (*endPointer != '\n');

		coords[i] = numBuffer;
	}
}

// default display function
void display(void (*fn)(void)) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.84, 0);              /* draw in golden yellow */
	glPointSize(1.0);                     /* size of each point */

	glBegin(GL_POINTS);

	(*fn)();

	glEnd();

	glFlush();                            /* render graphics */

	glutSwapBuffers();                    /* swap buffers */
}

void myinit() {
	glClearColor(0.0, 0.0, 0.92, 0.0);    /* blue background*/

	/* set up viewing */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

void scaleFactor(int x, int y, int r, float* buf) {
	int maxX = abs(x - r) > (x + r) ? abs(x - r) : x + r;
	int maxY = abs(y - r) > (y + r) ? abs(y - r) : y + r;

	float width = WINDOW_WIDTH;
	float height = WINDOW_HEIGHT;
	float widthScale = width / (float) (maxX * 2);
	float heightScale = height / (float) (maxY * 2);

	if (maxX > maxY) {
		buf[0] = widthScale;
		buf[1] = maxX;
	} else {
		buf[0] = heightScale;
		buf[1] = maxY;
	}
}

void scaleFactors(int** coordArr, float* buf) {
	buf[0] = INT_MAX;
	buf[1] = INT_MAX;

	int index = 0;
	int* current = coordArr[index];
	float tempBuf[2] = {0, 0};

	while (current != NULL) {
		scaleFactor(current[0], current[1], current[2], tempBuf);

		if (tempBuf[0] < buf[0]) {
			buf[0] = tempBuf[0];
			buf[1] = tempBuf[1];
		}

		index++;
		current = coordArr[index];
	}
}

void c(void) {
	draw_circle(c_x, c_y, c_r);
}

void displayC(void) {
	display(c);
}

void d(void) {
	// find scale factor and scale from world coordinate to screen coordinate
	float buffer[2];
	scaleFactors(coords, buffer);

	float factor = buffer[0];
	float max = buffer[1];

	printf("factor: %f max: %f\n", factor, max);

	int index = 0;
	int* current = coords[index];

	while (current != NULL) {
		int x = round((current[0] + max) * factor);
		int y = round((current[1] + max) * factor);
		int r = round(current[2] * factor);
		printf("x: %d y: %d r: %d\n", current[0], current[1], current[2]);
		printf("x': %d y': %d r': %d\n", x, y, r);
		printf("\n");

		draw_circle(x, y, r);
		index++;
		current = coords[index];
	}
}

void displayD(void) {
	display(d);
}

void e(void) {

}

void displayE(void) {
	display(e);
}
