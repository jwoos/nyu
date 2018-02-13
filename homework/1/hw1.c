#include <math.h>
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

void display(void);

void myinit(void);

void c(void);

void d(void);

void e(void);

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

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.84, 0);              /* draw in golden yellow */
	glPointSize(1.0);                     /* size of each point */

	glBegin(GL_POINTS);

	printf("Specify which part to run (c | d | e): ");
	char command = getchar();

	switch (command) {
		case 'c':
			c();
			break;
		case 'd':
			break;
		case 'e':
			break;

		default:
			printf("NOPE");
	}
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

void c(void) {
	printf("Enter the cx, cy and r separated by spaces: ");
	int x;
	int y;
	int r;
	scanf("%d %d %d", &x, &y, &r);

	printf("%d %d %d", x, y, r);
	draw_circle(x, y, r);
}

void d(void) {}

void e(void) {}
