#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
// #include <GL/glew.h>   // We don't need the GLEW library for now
#include <GLUT/glut.h>
#else
// #include <GL/glew.h>   // We don't need the GLEW library for now
#include <GL/glut.h>
#endif


#define XOFF          50
#define YOFF          50
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600


void draw_circle(int, int, int);

void file_in(void);

void display(void);

void myinit(void);

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	/* Use both double buffering and Z buffer */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(XOFF, YOFF);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CS6533/CS4533 Assignment 1");
	glutDisplayFunc(display);

	/* Function call to handle file input here */
	file_in();

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
	int r2 = pow(r, 2);

	while (2 * pow(currentY, 2) <= r2) {
		// first try
		if (!d) {
			d = 4 * pow(currentX, 2) - 4 * currentX + 1 + 4 * pow(currentY, 2) + 8 * currentY + 4 - 4 * r2;
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

		glPointSize(1.0);                     /* size of each point */

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

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.84, 0);              /* draw in golden yellow */
	glPointSize(4.0);                     /* size of each point */

	glBegin(GL_POINTS);
	switch (command) {
		case 'c':
			break;
		case 'd':
			break;
		case 'e':
			break;

		default:
			printf("NOPE");
	}
	glVertex2i(10, 10);
	draw_circle(300, 300, 30);
	glEnd();

	glFlush();                            /* render graphics */

	glutSwapBuffers();                    /* swap buffers */
}

void myinit() {
	glClearColor(0.0, 0.0, 0.92, 0.0);    /* blue background*/

	/* set up viewing */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}
