#include "Camera.h"
#include <math.h>
#include "raio.h"
#include <iostream>

Camera::Camera(Vetor& eye, Vetor& target, Vetor& up, double fov, double near, double far, int width, int height){
    this-> eye = eye;
    this-> target = target;
    this-> up = up;
    this-> fov = fov;
    this-> near = near;
    this-> far = far;
    this-> width = width;
    this-> height = height;

    altura = 2 * near * tan( fov / 2.0 );
    base = width / height * altura;

    ///Coordenadas da câmera
    ze = (eye - target).unitario();
    xe = (up%ze).unitario();
    ye = ze % xe;
}

Raio Camera::getRaio(double x, double y){
    double ux, vy, df;
    ux = base * (x / width - 0.5f);
    vy = altura * (y / height - 0.5f);
    df = -near;

    Vetor xtemp = xe * ux;
    Vetor ytemp = ye * vy;
    Vetor ztemp = ze * df;

    Vetor d = xtemp + ytemp + ztemp;

    Raio r = Raio( eye, d );
    return r;
}
