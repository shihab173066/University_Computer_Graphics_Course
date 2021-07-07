#include<windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define PI 3.1416

void initGL() {

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //background clear
   glOrtho(-1,1,-1,1,-1,1);


}
void triangle()
{
       glBegin(GL_TRIANGLES);

      glVertex2f(0.1f, -0.6f);
      glVertex2f(0.7f, -0.6f);
      glVertex2f(0.4f, -0.1f);
   glEnd();
}

void display() {

   glClear(GL_COLOR_BUFFER_BIT);// Buffer CLear

   glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(-100,0);
        glVertex2f(100,0);

        glVertex2f(0,-100);
        glVertex2f(0,100);
   glEnd();


   glBegin(GL_QUADS);
      glColor3f(1.0f, 0.33f, 0.64f);
      glVertex2f(-0.2f, -0.2f);
      glColor3f(1.0f, 0.33f, 0.64f);
      glVertex2f(0.2f, -0.2f);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(0.2f, 0.2f);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(-0.2f, 0.2f);

    glColor3f(1.0f, 0.33f, 0.64f);
      glVertex2f(-0.8f, 0.1f);
      glColor3f(0.1f, 0.9f, 0.84f);
      glVertex2f(-0.2f, 0.1f);
      glColor3f(1.0f, 0.33f, 0.64f);
      glVertex2f(-0.2f, 0.7f);
      glColor3f(1.0f, 0.33f, 0.64f);
      glVertex2f(-0.8f, 0.7f);


   glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    triangle();
    glColor3f(1.0f, 0.0f, 0.0f);
    triangle();

   glBegin(GL_POLYGON);
      glColor3f(1.0f, 1.0f, 0.0f);
      glVertex2f(0.4f, 0.2f);
      glVertex2f(0.6f, 0.2f);
      glVertex2f(0.7f, 0.4f);
      glVertex2f(0.6f, 0.6f);
      glVertex2f(0.4f, 0.6f);
      glVertex2f(0.3f, 0.4f);
   glEnd();

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
