#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include<stdio.h>

#define PI 3.1416

float tgt_x=0;
float tgt_y=0;
static float	tx	=  0.0;
static float	ty	=  0.0;

float minus_x=-25.0;
float plus_x=25.0;
float minus_y= -25.0;
float plus_y= 25.0;

int drawaxes;
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}

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

	glPushMatrix();             //Green Circle
	glTranslatef(-15.0,14.0,0);
    glColor3f(0.0, 1.0, 0.0);
	circle(6,6);
	glPopMatrix();


    glPushMatrix();             //Red circle (Static)
	glTranslatef(5.0,5.0,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(5,5);
	glPopMatrix();


    drawAxes();
	glFlush();
}

void init(void)
{
    drawaxes=1;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(minus_x, plus_x, minus_y,plus_y, -25.0,25.0);
}


void spe_key(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_LEFT:
				tx -=5;//tx=+5
				glutPostRedisplay();
				break;

		case GLUT_KEY_RIGHT:
				tx +=5;//tx=-5
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

void MyMouseFunc(int button, int action, int xPixel, int yPixel)
{

    if (button == 0 && action == GLUT_DOWN)
    {
        PlaySound("FROG.wav",NULL,ASYNC_MODE_COMPATIBILITY);
    }
    if(button == 2 && action == GLUT_DOWN )
    {

        if (yPixel<=250)
        {
            if(xPixel<=250)
            {
            tgt_x = (xPixel-250)/(250/25);//-625;
            tgt_y = (yPixel-250)/-(250/25);//325-
            }
            else
            {
            tgt_x = (xPixel-250)/(250/25);//-625;
            tgt_y = (yPixel-250)/-(250/25);//325-
            }

        }
        else{
            if(xPixel<=250)
            {
            tgt_x = (xPixel-250)/(250/25);//-625;
            tgt_y = (yPixel-250)/-(250/25);//325-
            }
            else{
            tgt_x = (xPixel-250)/(250/25);//-625;
            tgt_y = (yPixel-250)/-(250/25);//325-
            }
        }
            //if (xpixel<=250&&yPixel<=250)
            //else if(xpixel>250&&yPixel<=250)
            //PlaySound("giant.wav",NULL,ASYNC_MODE_COMPATIBILITY);
            //tgt_x = xPixel;//-625;
            //tgt_y = yPixel;//325-
            printf("x= %f, y=%f \n",tgt_x,tgt_y);

    }

    glutPostRedisplay();
}

int main()
{
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Circle");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(spe_key);
    //glutKeyboardFunc(my_keyboard);
    glutMouseFunc(MyMouseFunc);
	glutMainLoop();
	return 0;
}

