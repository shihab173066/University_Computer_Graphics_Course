#include<windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#define PI 3.1416

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //background clear
    glOrtho(-20,20,-20,20,-1,1);
}

void drawObjects()
{
    glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(-100,0);
    glVertex2f(100,0);

    glVertex2f(0,-100);
    glVertex2f(0,100);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.49,0.73,0.91);
    glVertex2f(5,7);
    glVertex2f(2,4);
    glVertex2f(8,4);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.23,0.48,0.34);
    glVertex2f(3,0);
    glVertex2f(7, 0);
    glVertex2f(7,4);
    glVertex2f(3,4);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.23,0.48,0.34);
    glVertex2f(-4,0);
    glVertex2f(0,4);
    glVertex2f(-4,8);
    glVertex2f(-8,4);
    glEnd();

    glBegin(GL_POLYGON);
    int  rx=6;
    int  ry=6;
    int  c=0;
    float theta1 = 0.0;

    glBegin(GL_POLYGON);
    glColor3f(1.0,0.75,0.0);
    glVertex2f(0.0f,0.0f);
    for(c = 100; c <=140; c++)
    {
        theta1 =  PI * c /100;
        glVertex2f (cos(theta1) * rx, sin(theta1) * ry);
    }

    glEnd();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);// Buffer CLear
    drawObjects();
    glFlush(); //render
}

int main()
{
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("My_First_GL_program_011173066");
    initGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
