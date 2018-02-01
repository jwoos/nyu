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


void display(void);
void myinit(void);

/* Function to handle file input; modification may be needed */
void file_in(void);

/*-----------------
The main function
------------------*/
int main(int argc, char **argv)
{
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

/*----------
file_in(): file input function. Modify here.
------------*/
void file_in(void)
{

}


/*---------------------------------------------------------------------
display(): This function is called once for _every_ frame.
---------------------------------------------------------------------*/
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.84, 0);              /* draw in golden yellow */
    glPointSize(4.0);                     /* size of each point */

    glBegin(GL_POINTS);
    glVertex2i(600, 600);               /* draw a vertex here */
    glEnd();

    glFlush();                            /* render graphics */

    glutSwapBuffers();                    /* swap buffers */
}

/*---------------------------------------------------------------------
myinit(): Set up attributes and viewing
---------------------------------------------------------------------*/
void myinit()
{
    glClearColor(0.0, 0.0, 0.92, 0.0);    /* blue background*/

    /* set up viewing */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}
