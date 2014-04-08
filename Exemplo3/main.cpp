/*
 Use up    and down arrow keys to tip  the teapot.
 Use right and left arrow keys to turn the teapot.
 
 Mike Werner - Nov. 11, 2008 - [email]Werner_321@hotmail.com[/email]
 */

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>

short wire = 1;

float w, h, tip = 0, turn = 0;

float ORG[3] = {0,0,0};

float XP[3] = {1,0,0}, XN[3] = {-1,0,0},
YP[3] = {0,1,0}, YN[3] = {0,-1,0},
ZP[3] = {0,0,1}, ZN[3] = {0,0,-1};

void reshape (int nw, int nh)
{
    w = nw;
    h = nh;
}

void Keybord (int key, int x, int y)
{
    switch (key) {
        case  'w' : wire = !wire;  break;
        case   27 : exit (0);
        default   : printf ("   %c == %3d from Keybord\n", key, key);
    }
}

void Special (int key, int x, int y)
{
    switch (key) {
        case  GLUT_KEY_RIGHT: turn += 5;  break;
        case  GLUT_KEY_LEFT : turn -= 5;  break;
        case  GLUT_KEY_UP   : tip  -= 5;  break;
        case  GLUT_KEY_DOWN : tip  += 5;  break;
            
        default : printf ("   %c == %3d from Special\n", key, key);
    }
}

void Draw_Axes (void)
{
    glPushMatrix ();
    
    glTranslatef (-2.4, -1.5, -5);
    glRotatef    (tip , 1,0,0);
    glRotatef    (turn, 0,1,0);
    glScalef     (0.25, 0.25, 0.25);
    
    glLineWidth (2.0);
    
    glBegin (GL_LINES);
    glColor3f (1,0,0);  glVertex3fv (ORG);  glVertex3fv (XP);    // X axis is red.
    glColor3f (0,1,0);  glVertex3fv (ORG);  glVertex3fv (YP);    // Y axis is green.
    glColor3f (0,0,1);  glVertex3fv (ORG);  glVertex3fv (ZP);    // z axis is blue.
    glEnd();
    
    glPopMatrix ();
}

void Draw_Teapot (void)
{
    glPushMatrix ();
    
    glTranslatef (0, 0, -5);
    glRotatef (tip , 1,0,0);
    glRotatef (turn, 0,1,0);
    
    glColor3f (1.0, 0.5, 0.1);
    glutSolidTeapot (1.0);
    
    if (wire)  {
        glLineWidth (2.0);
        glColor3f (0.0, 0.2, 0.9);
        glutWireTeapot (1.01);
    }
    
    glPopMatrix ();
}

void display (void)
{
    glViewport (0, 0, w, h);
    glClear    (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Draw_Teapot ();
    Draw_Axes ();
    
    glutSwapBuffers ();
}

int main (void)
{
    glutInitWindowSize     (600, 400);
    glutInitWindowPosition (400, 300);
    glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow       ("Corner Axes");
    glutDisplayFunc        (display);
    glutIdleFunc           (display);
    glutReshapeFunc        (reshape);
    //glutKeyboardFunc       (Keybord);
    glutSpecialFunc        (Special);
    
    glClearColor   (0.1, 0.2, 0.1, 1.0);
    glEnable       (GL_DEPTH_TEST);
    glMatrixMode   (GL_PROJECTION);
    gluPerspective (40.0, 1.5, 1.0, 10.0);
    glMatrixMode   (GL_MODELVIEW);
    
    glutMainLoop ();
}