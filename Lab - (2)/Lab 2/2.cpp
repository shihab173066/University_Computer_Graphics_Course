#include<windows.h>
#include <GL/glut.h>


void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
}

static float p=-100.0; //initially set the quad to the leftmost corner of the screen

void display(void)
{

   glClear(GL_COLOR_BUFFER_BIT);

   glPushMatrix();

   glTranslatef(0,p,0);

   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_QUADS);
   glColor3f(0.0, 0.5, 1.0);
   glVertex2f(25,25);
   glColor3f(1.0, 0.5, 1.0);
   glVertex2f(-25,25);
   glVertex2f(-25,-25);
   glVertex2f(25,-25);
   glEnd();



    glBegin(GL_TRIANGLES);
   glColor3f(1.0, 1.5, 1.0);
   glVertex2f(-25,25);
   glVertex2f(25,25);
   glVertex2f(0,50);

   glEnd();



   glPopMatrix();

	glFlush();

	if(p<=100.0)
        p=p+0.09; //every time when the value of p increases, it moves a little bit right

    else
        p=-100; //when the quad reaches the right end of the screen, set the value of p again to -100, that is the leftmost screen value

   glutPostRedisplay();//calls the display func again


}

int main()
{
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Continuous Movement");
	init();
    glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
