#include<windows.h>
#include <GL/glut.h>

static float spin = 0.0;
static float	tx	=  0.0;
static float	ty	=  0.0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

        glRotatef(spin, 0.0, 0.0, 1.0);
        glTranslatef(tx,ty,0);
        glRectf(-25.0, -25.0, 25.0, 25.0);

    glPopMatrix();
    glFlush();
}

void spinDisplay_left(void)
{
    spin = spin + 0.2;
    glutPostRedisplay();
}

void spinDisplay_right(void)
{
    spin = spin - 0.2;
    glutPostRedisplay();
}


void init(void)
{
    //glEnable(GL_DEPTH_TEST);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(-100.0, 100.0, -100.0,100.0, 0.0, 1.0);
}


void my_keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {

    case 'l':
        glutIdleFunc(spinDisplay_left);
        break;

    case 'r':
        glutIdleFunc(spinDisplay_right);
        break;

    case 's':
        glutIdleFunc(NULL);
        break;

    default:
        break;
    }
}

void spe_key(int key, int x, int y)
{

    switch (key)
    {

    case GLUT_KEY_UP:
        ty +=5;
        PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
        glutPostRedisplay();
        break;



    case GLUT_KEY_DOWN:

        ty -=5;
        PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        tx +=5;
        PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
        glutPostRedisplay();
        break;



    case GLUT_KEY_LEFT:
        tx -=5;
        PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
        glutPostRedisplay();
        break;



    default:
        break;
    }
}


void my_mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay_left);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay_right);

        break;
    default:
        break;
    }
}

int main()
{
    //PlaySound("Horn Honk-SoundBible.com-1162546405.wav", NULL, SND_FILENAME| SND_ASYNC);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);

    glutCreateWindow ("Shihab_Class_02");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(my_keyboard);
    glutSpecialFunc(spe_key);
    glutMouseFunc(my_mouse);
    glutMainLoop();
    return 0;
}
