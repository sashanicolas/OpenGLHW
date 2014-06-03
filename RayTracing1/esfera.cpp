/*
 * File:   esfera.cpp
 * Author: jefersonromulo
 *
 * Created on 12 de Junho de 2011, 16:15
 */

#include "esfera.h"
#include "raio.h"
#include "Vetor.h"
#include <cmath>
#include <iostream>

using namespace std;

Esfera::Esfera(material m) : Geometria(m){
}

Esfera::Esfera(Vetor& centro, double raio,material m) : Geometria(m){
    this->centro = centro;
    this->raio = raio;
}

Esfera::~Esfera(){

}

Vetor Esfera::getNormal(Vetor& ponto){
    Vetor v;
    v = ponto - centro;
    double n = v.Norma( );
    Vetor norm;
    norm = v * (1.0f / n);
    return norm;
}

double Esfera::intersecao(Raio& r){
    Vetor d = r.dir;
    Vetor o = r.origem;

    double a = d * d;
    double b = d * (o - centro) * 2;
    double c = (o - centro) * (o - centro) - raio * raio;

    double delta = b * b - 4 * a * c;

    if ( delta >= 0 ){
        double t1 = (-b - sqrt( delta )) / (2 * a);
        double t2 = (-b + sqrt( delta )) / (2 * a);

        if ( t1 < t2 ){
            return t1;
        }else{
            return t2;
        }
    }else{
        return delta;
    }
}
