#include<bits/stdc++.h>
#include<windows.h>
#include<GL/glut.h>

#define pi (2*acos(0.0))

/**
    Name: Md. Shihab Hossain Auni

    Id: 011173066 (United International University student Id)

    Email: mhossain173066@bscse.uiu.ac.bd, shihab.hossainSH@gmail.com

    Contact: 01622789743
*/

/**----------------------------------------Global variables------------------------------------------------------------------------------------------*/

float tx = 0.0, ty = 0.0, tx1 = 0.0, ty1 = 0.0, tz1=0.0, ball_x=-60, ball_y=100.0, ball_z= 0.0;
int timerStart = 0, gameover = 0, elapsedTime = 0, col = 0, flag=0, flag1=0, ball_r=10, ball_r1=5, state, state1, score=0, lastscore=0, count = 0;
double ball_speed = 0.7, angle, incx, incy;
bool stateSave = true;
void* currentFont;

/**--------------------------------------------------------------------------------------------------------------------------------------------------*/

struct point
{
	double x,y,z;
};

void drawAxes()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glVertex3f( 100,0,0);
        glVertex3f(-100,0,0);

        glVertex3f(0,-100,0);
        glVertex3f(0, 100,0);

        glVertex3f(0,0, 100);
        glVertex3f(0,0,-100);
    }glEnd();
}

void setFont(void* font)
{
    currentFont = font;
}

void drawString(float x, float y, float z, char *string)
{
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++)
  {
        glutBitmapCharacter(currentFont, *c);  // Updates the position
  }
}

void timer(int x)
{
    lastscore+=1;
    stateSave = false;
    count = 0;
    glutPostRedisplay();

}
void exitProg(int x)
{
    printf("------------------------\nGAME OVER......!!!\n\nYour score: %d\n", lastscore);
    printf("\nYour Survival Time: %d\n------------------------", elapsedTime+1);
    exit(0);

}

void timer2(int x)
{
    stateSave = true;
    count = 0;
    glutPostRedisplay();
}

void elapsedTimer(int x)
{
    if((elapsedTime % 10 == 0) && (elapsedTime != 0))
    {
        ball_speed += 0.1;
    }
    if((elapsedTime % 20 == 0))
    {
        ball_speed += 0.05;
    }
    elapsedTime += 1;
    glutTimerFunc(1000, elapsedTimer, 0);
    glutPostRedisplay();
}

bool collision(float s1_x, float s1_y, float s1_z, int s1_radius, float s2_x, float s2_y, float s2_z, int s2_radius)
{
    double value =(((s1_x - s2_x) * (s1_x - s2_x)) + ((s1_y - s2_y) * (s1_y - s2_y)) + ((s1_z - s2_z) * (s1_z - s2_z)));
    double distance = sqrt(value);

    return distance <= 20;
}

void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;

            ///lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            ///lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }
    glEnd();
}

void drawSquare(double a,double b)
{
	glBegin(GL_QUADS);{
		glVertex3f( a, 0,2);
		glVertex3f( a,-b,2);
		glVertex3f(-a,-b,2);
		glVertex3f(-a, 0,2);
	}glEnd();
}

void drawCircle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);
    {
		for(i = 0; i < 100; i++)
		{
			angle = 2 * 3.1416 * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}
    }
	glEnd();
}

void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	///generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	///draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f(col,1,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    ///upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                ///lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}
			glEnd();
		}
	}
}
void drawSphere1(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	///generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	///draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        ///glColor3f((double)i/(double)stacks,1,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    ///upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                ///lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void brick()
{
    ///bricks1
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(193,-189,0);
    drawSquare(14,18);
    glPopMatrix();
    ///bricks2
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(184.5,-170,0);
    drawSquare(23,18);
    glPopMatrix();
    ///bricks3
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(158,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks4
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(140.5,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks5
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(117,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks6
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(100,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks7
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(76,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks8
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(59,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks9
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(35,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks10
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(18,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks11
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-6.01,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks12
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-23,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks13
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-47,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks14
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-64,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks15
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-88,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks16
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-105,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks17
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-129,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks18
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-145.8,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks19
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-170,-189,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks20
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-187,-170,0);
    drawSquare(20,18);
    glPopMatrix();
    ///bricks21
    glPushMatrix();
    glColor3f(0.7, 0.3, 0.2);
    glTranslatef(-199,-189,0);
    drawSquare(8,18);
    glPopMatrix();
    ///background black
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0,-170,0);
    drawSquare(209,40);
    glPopMatrix();
}

void ghost(void)
{
    glTranslatef(tx,ty,0);
    glScalef(5,5,0);
    ///headEyeCenter:
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1,0);
    drawCircle(1.5,1.5);
    glPopMatrix();
    ///headEyeBlack:
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1,0);
    drawCircle(2.5,2.5);
    glPopMatrix();
    ///headmiddle:
    glColor3f(0.0, 0.0, 10.0);
    glPushMatrix();
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1-5,0);
    glBegin(GL_POLYGON);
    glVertex2f(5, 5);
    glVertex2f(5, -1);
    glVertex2f(-5, -1);
    glVertex2f(-5, 5);
    glEnd();
    glPopMatrix();
    ///headup:
    glPushMatrix();
    glColor3f(col, 10.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(0, 0, 0);
    drawSphere(ball_r1,30,30);
    glPopMatrix();
    ///body:
    glPushMatrix();
    glColor3f(0.0, 10.0, 0.0);
    glScalef(1,1,0.0);
    glTranslatef(tx1,ty1-10,0);
    glBegin(GL_POLYGON);
    glVertex2f(4, 5);
    glVertex2f(8, 1);
    glVertex2f(-8, 1);
    glVertex2f(-4, 5);
    glEnd();
    glPopMatrix();
}

void ballupdate()
{
    if(!flag)
    {
        ball_y+=ball_speed;
        if(ball_y>200.0)
        {
            flag=1;
        }
    }
    if(flag)
    {
        ball_y-=ball_speed;
        if(ball_y<-165)
        {
            flag=0;
        }
    }
}

void ball()
{
    float b=0.0;
    drawSphere(ball_r,10,10);
}

void key(int key, int x, int y)
{
	switch (key)
	{
        case GLUT_KEY_LEFT:
            tx=tx-2;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            tx=tx+2;
            glutPostRedisplay();
            break;
	}
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(184.0f/255.0f, 213.0f/255.0f, 238.0f/255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(0,0,250,	0,0,0,	0,1,0);

    char str[80];
        sprintf(str, "Survival Score: [%d]", lastscore);

        glColor3f(0,0,0); /// black color
        drawString(133, 190, 0, str);
    char STR[80];
        sprintf(STR, "Survival Time: [%d]seconds", elapsedTime);

        glColor3f(0,0,0); /// black color
        drawString(98, 170, 0, STR);



	glPushMatrix();
        glTranslatef(ball_x, ball_y, 0);
        ball();
    glPopMatrix();
    brick();

    glPushMatrix();
    glTranslatef(tx1, ty1-140, 0);
    ghost();
    glPopMatrix();

	glutSwapBuffers();
}


void animate()
{
    ballupdate();
    angle=0.005;

    if(collision(tx, ty1-140, 0, ball_r1, ball_x, ball_y, ball_z, ball_r))
    {
        col = 1;
        gameover = 1;
        glutTimerFunc(1500, exitProg, 0);
    }

    if(count == 0)
    {
        if(stateSave)
        {
            glutTimerFunc(1000, timer, 0);
        }
        else
        {
            glutTimerFunc(1000, timer2, 0);
        }
        count = 1;
    }

    if(timerStart == 0)
    {
        glutTimerFunc(1000, elapsedTimer, 0);
        timerStart = 1;
    }

    if(gameover != 1){
        if(state ==0 && ball_x>=218){state =1;}
        if(state ==1 && ball_x <-218){state =0;}

        if(state == 0) ball_x += 0.1;
        else ball_x -= 0.1;

        if(state1 ==0 && incy>500){state1 =1;
        glRotated(angle,0,0,1);}
        if(state1 ==1 && incy<-500){state1 =0;
        glRotated(-angle,0,1,1);}

        if(state1 == 0) ball_y += 0.1;
        else ball_y -= 0.1;
    }

    if(gameover)
    {
        ball_x = 0; ball_y = 0;
    }


	glutPostRedisplay();
}

void init()
{
	glClearColor(0,0,0,0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(80,	1,	1,	1000.0);
	setFont(GLUT_BITMAP_HELVETICA_18);

}


int main(int argc, char **argv)
{
	glutInit(&argc,argv);

	glutInitWindowSize(900, 700);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Dodge Ball By Md. Shihab Hossain");

	init();

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	glutSpecialFunc(key);
	glutMainLoop();
	return 0;
}
