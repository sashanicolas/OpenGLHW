#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "color.h"

// Initialization function
static void Init ()
{
    float white[4] = {1.0f,1.0f,1.0f,1.0f};
    glClearColor(0, 0, 0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50.0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
}

// Draw scene
static void DrawAxes ()
{
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(20, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 20, 0);
    
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);
    glEnd();
}


// Draw scene
static void DrawScene ()
{
    // position light
    float lpos[4] = {0.0f,100.0f,0.0f,1.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,lpos);
    
    float lambda=380.0, delta = 0.2;
    float x, y, z;
    float s = 20.0;

    while (lambda<780.0) {
        
        corGetCIExyz(lambda, &x, &y, &z);
        glBegin(GL_POINT);
            glColor3f(s*x, s*y, s*z);
        glEnd();
        
        printf("%f %f %f %f\n",lambda,x,y,z);
        
        lambda += delta;
    }
}

// Display callback
static void Display (void)
{
    int vp[4];
    glGetIntegerv(GL_VIEWPORT,vp);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f,(float)vp[2]/vp[3],1.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // load manipulator matrix
    gluLookAt(5,10,30,
              5,5,0,
              0,1,0);
    
    DrawAxes();
    DrawScene();
    
    glutSwapBuffers();
}

// Reshape callback
static void Reshape (int w, int h)
{
    glViewport(0,0,w,h);
}

// Keyboard callback
static void Keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: exit(0); break;
    }
}

// Main function
int main (int argc, char* argv[])
{
    // open GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800,600);
    
    // create window
    glutCreateWindow ("Spheres");
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    
    // initiate OpenGL context
    Init();
    
    // interact...
    glutMainLoop();
    return 0;
}
