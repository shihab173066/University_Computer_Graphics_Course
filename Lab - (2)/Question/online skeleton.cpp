#include<windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define PI 3.1416

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //background clear
   glOrtho(-1,1,-1,1,-1,1);
}

void drawObjects(){
}

void display() {

   glClear(GL_COLOR_BUFFER_BIT);// Buffer CLear
   drawObjects();
   glFlush(); //render
}

int main()
{
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("My_First_GL_program");
    initGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
