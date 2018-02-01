#include <stdlib.h>
#include <stdio.h>

// #include <GL/glew.h>   // We don't need the GLEW library for now
#include <GL/glut.h>


#define XOFF          50
#define YOFF          50
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600


void draw_circle(int, int, int);

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

}
