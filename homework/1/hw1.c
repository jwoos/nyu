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

float scaleFactor(int, int, int);

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

	glutDisplayFunc(fn);

	/* Function call to handle file input here */
	/*file_in();*/

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
	int d = 0;
	int r2 = r * r;

	while (2 * (currentY * currentY) <= r2) {
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

		// shift by x and y to draw a line that is not centered on origin
		shiftedX = currentX + x;
		shiftedXn = -currentX + x;
		shiftedY = currentY + y;
		shiftedYn = -currentY + y;

		glVertex2i(shiftedX, shiftedY);
		glVertex2i(shiftedXn, shiftedY);
		glVertex2i(shiftedX, shiftedYn);
		glVertex2i(shiftedXn, shiftedYn);

		glVertex2i(shiftedY, shiftedX);
		glVertex2i(shiftedYn, shiftedX);
		glVertex2i(shiftedY, shiftedXn);
		glVertex2i(shiftedYn, shiftedXn);

		currentY++;
	}
}

void file_in(void) {
	char* filename = "input_circles.txt";
	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Error opening file\n");
		exit(1);
	}

	char buffer[100];
	// get first number
	fgets(buffer, 100, f);
	int num = strtol(buffer, NULL, 10);
	int* numBuffer;
	coords = malloc(sizeof(int*) * num);

	for (int i = 0; i < num; i++) {
		coords[i] = malloc(sizeof(int) * 3);
		fgets(buffer, 100, f);
		sscanf(buffer, "%d %d %d", coords[i], coords[i] + 1, coords[i] + 2);
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

float scaleFactor(int x, int y, int r) {
	int maxX = abs(x - r) > x + r ? abs(x - r) : x + r;
	int maxY = abs(y - r) > y + r ? abs(y - r) : y + r;

	float width = WINDOW_WIDTH;
	float height = WINDOW_HEIGHT;
	float widthScale = width / (float) maxX;
	float heightScale = height / (float) maxY;

	printf("widthScale: %f heightScale: %f\n", widthScale, heightScale);

	return widthScale > heightScale ? widthScale : heightScale;
}

void c(void) {
	draw_circle(c_x, c_y, c_r);
}

void displayC(void) {
	display(c);
}

int d_x = 0;
int d_y = 0;
int d_r = 50;
void d(void) {
	// find scale factor and scale from world coordinate to screen coordinate
	float factor = scaleFactor(d_x, d_x, d_r);
	int rad = round(d_r * factor / 2);
	draw_circle(d_x + rad, d_y + rad, rad);
}

void displayD(void) {
	display(d);
}

void e(void) {

}

void displayE(void) {
	display(e);
}
