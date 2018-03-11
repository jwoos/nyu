/************************************
 * Handout: example.cpp
 *
 * This program is to demonstrate the basic OpenGL program structure.
 * Read the comments carefully for explanations.
 ************************************/

#include <stdio.h>
#include <math.h>

#ifdef __APPLE__  // include Mac OS X verions of headers
#include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#include <GL/glut.h>
#endif

float f = 0.0;

void display(void);
void my_init(void);
void reshape(int w, int h);
void idle(void);

int main(int argc, char **argv) {
	/*---- Initialize & Open Window ---*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double-buffering and RGB color
	// mode.
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(30, 30);  // Graphics window position
	glutCreateWindow("Rectangle"); // Window title is "Rectangle"

	/*--- Register call-back functions; any order is fine ---*/
	/* Events: display, reshape, keyboard, mouse, idle, etc.

	   - display: Automatically called when the window is first opened.
	   Later, when the frame content needs to be changed, we need
	   to call display again From the Program to re-draw the objects.
	   This is essential for animation.
	   - reshape: Automatically called when the window is first opened,
	   or when the window is re-sized or moved by the user.
	   - keyboard: Automatically called when a keyboard event occurs.
	   - mouse:    Automatically called when a mouse event occurs.
	   - idle:     Automatically called when nothing occurs.
	   This is essential for animation.

	 * Once entering the event loop, the execution control always returns to
	 the event loop. When particular event occurs, the corresponding call-back
	 function is called; when that call-back function finishes, control again
	 goes back to the event loop, and the process is repeated.

*/
	glutDisplayFunc(display); // Register our display() function as the display
	// call-back function
	glutReshapeFunc(reshape); // Register our reshape() function as the reshape
	// call-back function
	// glutMouseFunc(mouse);  // for mouse
	// glutKeyboardFunc(key); // for keyboard
	glutIdleFunc(idle);       // Register our idle() function

	my_init();                // initialize variables

	glutMainLoop();          // Enter the event loop

	return 0;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);  // clear frame buffer (also called the
	// color buffer)
	glColor3f(0.0, 1.0, 1.0);      // draw in cyan.
	// The color stays the same until we
	// change it next time.

	glBegin(GL_POLYGON);           // Draw a polygon (can have many vertices)
	// The vertex coordinates change by different
	// values of f; see also function idle().
	glVertex2f(100, 100 + f);
	glVertex2f(200, 100 + f);
	glVertex2f(200, 300 + f);
	glVertex2f(100, 300 + f);
	glEnd();

	glFlush();         // Render (draw) the object
	glutSwapBuffers(); // Swap buffers in double buffering.
}

void my_init() {
	glClearColor(0.0, 0.0, 0.0, 0.0); // Use black as the color for clearing
	// the frame buffer (also called the
	// color buffer). This produces a
	// black background.
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);           // Viewport within the graphics window.

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void idle(void) {
	f += 1.0;  // smaller number gives a slower but smoother animation

	if (f > 180.0) f = 0.0;

	glutPostRedisplay(); // or call display()
}
