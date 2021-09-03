#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#define pi (2*acos(0.0))

struct point;

void drawCone(double radius,double height,int segments);


struct point{
    double x,y,z;
};


float speedOfCamera = 2; //Camera x,y,z coordinate change
struct point eye= {100,100,100}; //Perspective Projection Parameter
struct point up = {1,0,0}; /// m = 066 % 3 = 0 (up axis is x) //Perspective Projection Parameter, change according id

bool perspectiveOrOrthographic = true;//Change According to your id

void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
    }glEnd();

}


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}



void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(eye.x,eye.y,eye.z,	0,0,0,	up.x,up.y ,up.z);

    glMatrixMode(GL_MODELVIEW);

	drawAxes();
	drawGrid();

	/****************************
	/ Add your objects from here
	****************************/
	glPushMatrix();
        glScaled(1.2, 1.2, 0.8);
        drawCone(20, 45, 40);
    glPopMatrix();

	glFlush();
	glutSwapBuffers();
}


void animate(){

	//codes for any changes in Models, Camera
	glutPostRedisplay(); // marks the current window as needing to be redisplayed
}

void init(){
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if(perspectiveOrOrthographic == true)
    {
        gluPerspective(80,	1,	1,	5000.0); /// as my id last digit is even 011173066
    }
    else
    {
        glOrtho(-100,100,-100,100,0,200);
    }
}


void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void myKeyBoard(unsigned char key, int x, int y){

    switch (key) {
        case '1':
            eye.x += speedOfCamera;///'1' => eye x increase
            break;

        case '2':
            eye.x -= speedOfCamera;///'2' => eye x decrease
            break;

        case '3':
            eye.y += speedOfCamera;///'3' => eye y increase
            break;

        case '4':
            eye.y -= speedOfCamera;///'4' => eye y decrease
            break;

        case '5':
            eye.z += speedOfCamera;///'5' => eye z increase
            break;

        case '6':
            eye.z -= speedOfCamera;///'6' => eye z decrease
            break;
    }

    glutPostRedisplay();
}

void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
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
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	/*
	GLUT_DOUBLE - allows for display on the double buffer window

    GLUT_RGB - shows color (Red, green, blue)

    GLUT_DEPTH - allows for depth buffer
    */

	glutCreateWindow("Shihab-011173066 OpenGL Program Assignment-02");

	init();

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
    glutKeyboardFunc(myKeyBoard);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
