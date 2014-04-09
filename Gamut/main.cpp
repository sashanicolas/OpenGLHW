#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "color.h"

float k;

// Initialization function
static void Init(){
    float white[4] = {1.0f,1.0f,1.0f,1.0f};
    glClearColor(0, 0, 0, 1.0f);
    //glEnable(GL_DEPTH_TEST);
    
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_NORMALIZE);
    //glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    //glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50.0);
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
}

// Draw scene
static void DrawAxes(){
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

//Draw Cube limts
static void DrawCube(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, 0);
    
    glVertex3f(1, 1, 1);
    glVertex3f(0, 1, 1);
    
    glVertex3f(1, 1, 1);
    glVertex3f(1, 0, 1);
    
    glVertex3f(0, 1, 1);
    glVertex3f(0, 0, 1);
    
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    
    glVertex3f(1, 1, 0);
    glVertex3f(0, 1, 0);
    
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    
    glVertex3f(0, 1, 1);
    glVertex3f(0, 1, 0);
    
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 1);
    glEnd();
}

//calcula valor da componente k para um lambda
void calculateK(float *k){
    float aux = 0, y_bar, x_bar, z_bar;
    for (int lambda=380; lambda<=780; lambda++) {
        corGetCIExyz(lambda, &x_bar, &y_bar, &z_bar);
        aux += corGetD65(lambda) * y_bar;
    }
//    printf("%f;\n",aux);
    *k = 1.0 / aux;
}

//retorna uma cor XYZ, usa k global
void getColorXYZ(float *X, float *Y, float *Z){
    float beta[401];
    for (int i=0; i<=400; i++) {
        beta[i] = ( rand() % 100 ) / 100.0;
        printf("%f;\n",beta[i]);
    }
    
    float x_bar, y_bar, z_bar, L;
    *X = 0; *Y = 0; *Z = 0;
    
    for (int lambda=380; lambda<=780; lambda++) {
        corGetCIExyz(lambda, &x_bar, &y_bar, &z_bar);
        L = corGetD65(lambda);
        
        *X += beta[lambda - 380] * L * x_bar;
        *Y += beta[lambda - 380] * L * y_bar;
        *Z += beta[lambda - 380] * L * z_bar;
    }
    
    *X *= k;
    *Y *= k;
    *Z *= k;
    
}

// Draw scene
static void DrawScene(){
    // position light
//    float lpos[4] = {0.0f,100.0f,0.0f,1.0f};
    //glLightfv(GL_LIGHT0,GL_POSITION,lpos);

    float X, Y, Z;
    float r, g, b;

    //desenhar cubo limitante
    DrawCube();
    
    int n = 0;
    calculateK(&k);

    glBegin(GL_POINTS);
    while (n<1) {
        getColorXYZ( &X, &Y, &Z);
        corCIEXYZtoCIERGB(X,Y,Z, &r, &g, &b);
        
        //printf("%f; %f; %f;\n",r,g,b);
        
        glColor3f(r, g, b);
        glVertex3f(r, g, b);
        
        n++;
    }
    glEnd();
    
}

// Display callback
static void Display (void){
    int vp[4];
    glGetIntegerv(GL_VIEWPORT,vp);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f,(float)vp[2]/vp[3],1.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // load manipulator matrix
    gluLookAt(-2.5,1.5,2,
              0.5,0.5,0.5,
              0,1,0);
    
    DrawAxes();
    DrawScene();
    
    glutSwapBuffers();
}

// Reshape callback
static void Reshape (int w, int h){
    glViewport(0,0,w,h);
}

// Keyboard callback
static void Keyboard (unsigned char key, int x, int y){
    switch (key){
        case 27: exit(0); break;
    }
}

// Main function
int main (int argc, char* argv[]){
    srand(time(NULL));
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


