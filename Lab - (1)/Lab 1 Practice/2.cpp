#include<windows.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1416

static float	tx	=  0.0;
static float	ty	=  0.0;

void circle(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
			//glVertex2f (cos(angle) * radius_x+5, sin(angle) * radius_y);
		}

	glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();             //Green Circle
	glTranslatef(tx,ty,0);
    glColor3f(0.0, 1.0, 0.0);
	circle(6,6);
	glPopMatrix();

    glPushMatrix();             //Red circle (Static)
	glTranslatef(5.0,5.0,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(5,5);
	glPopMatrix();

	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
}


void spe_key(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_LEFT:
				tx -=5;
				glutPostRedisplay();
				break;

		case GLUT_KEY_RIGHT:
				tx +=5;
				glutPostRedisplay();
				break;

        case GLUT_KEY_DOWN:
				ty -=5;
				glutPostRedisplay();
				break;

		case GLUT_KEY_UP:
				ty +=5;
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}


int main()
{
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Circle");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(spe_key);
	glutMainLoop();
	return 0;
}

