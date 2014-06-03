#ifndef CAMERA_H
#define	CAMERA_H

#include "Vetor.h"
#include "raio.h"

class Camera {
public:
    Camera(Vetor& eye, Vetor& target, Vetor& up, double fov, double near, double far, int w, int h);
    Raio getRaio(double x, double y);

    Vetor eye;
    Vetor target;
    Vetor up;

    double fov;
    double near;
    double far;
    int width;
    int height;
    double base;
    double altura;
    Vetor xe, ye, ze; ///Sistema do eye
};

#endif	/* CAMERA_H */
