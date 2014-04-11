#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "color.h"

#define nPoints 10000

float k;
float points[nPoints][3];

// Camera position
float x_cam = -2.5, z_cam = 2; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, lz = 0.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts



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
    int c=0;
    float aux, prox, valor;
    beta[0]=0;

    //repete ou aumenta/diminue
    while (c<401) {
        if (rand()%2 == 0) { // repete
        //if(1==0){
            aux = rand() % 80 ; //quantos vao ter o mesmo valor
            beta[c] = ( rand() % 100 ) / 100.0; // o valor em si
            for (int i=0; i<=aux && c+i<401; i++) {
                beta[c+i] = beta[c];
            }
            c+=aux;
        }else{// 1 - aumenta ou diminue
            prox = rand() % 50 ; //proximo
            valor = ( rand() % 100 ) / 100.0; //valor do proximo
            for (int i=1; i<=prox && c+i<401; i++) {
                beta[c+i] = beta[c] + (valor-beta[c])/(float)i;
            }
            c+=prox;
        }
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

    //desenhar cubo limitante
    DrawCube();

    glBegin(GL_POINTS);
    for (int i=0; i<nPoints; i++) {
        glColor3f(points[i][0], points[i][1], points[i][2]);
        glVertex3f(points[i][0], points[i][1], points[i][2]);
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
    gluLookAt(x_cam, 1.5, z_cam,
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
    
    
    float X, Y, Z;
    float r, g, b;
    
    int n = 0;
    calculateK(&k);

    while (n<nPoints) {
        getColorXYZ( &X, &Y, &Z);
        corCIEXYZtoCIERGB(X,Y,Z, &r, &g, &b);
        
        points[n][0] = r;
        points[n][1] = g;
        points[n][2] = b;
        
        n++;
    }
}

//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update(void)
{
	if (deltaMove) { // update camera position
	//	x_cam += deltaMove * lx * 0.1;
	//	z_cam += deltaMove * lz * 0.1;
	}
	glutPostRedisplay(); // redisplay everything
}

//----------------------------------------------------------------------
// Process mouse drag events
//
// This is called when dragging motion occurs. The variable
// angle stores the camera angle at the instance when dragging
// started, and deltaAngle is a additional angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void mouseMove(int x, int y)
{
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;
        
		// camera's direction is set to angle + deltaAngle
		//lx = -sin(angle + deltaAngle);
		//lz = cos(angle + deltaAngle);
        
        lx = cos(angle + deltaAngle);
        printf("%f\n",lx);

        lz = sin(angle + deltaAngle);
        printf("%f\n",lz);

        x_cam += lx;
        z_cam += lz;
	}
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
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
    glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
    glutIdleFunc(update); // incremental update
	
    
    // initiate OpenGL context
    Init();
    
    // interact...
    glutMainLoop();
    return 0;
}


