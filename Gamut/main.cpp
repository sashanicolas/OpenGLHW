#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Initialization function
static void Init ()
{
    float white[4] = {1.0f,1.0f,1.0f,1.0f};
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
static void DrawScene ()
{
    // position light
    float lpos[4] = {0.0f,100.0f,0.0f,1.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,lpos);
    
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
    gluLookAt(0,7,15,0,0,0,0,1,0);
    
    
    // draw scene
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
