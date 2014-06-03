#include "Vetor.h"
#include <iostream>
#include <math.h>

using namespace std;

Vetor::Vetor(){
    x = 0;
    y = 0;
    z = 0;
}

Vetor::Vetor(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vetor::Vetor(const Vetor& orig){
    x = orig.x;
    y = orig.y;
    z = orig.z;
}

Vetor::~Vetor(){
}

double Vetor::Norma(){
    double norma = sqrt( x * x + y * y + z * z );
    return norma;
}

Vetor Vetor::operator +(const Vetor& v){
    Vetor r = *this;
    r.x = r.x + v.x;
    r.y = r.y + v.y;
    r.z = r.z + v.z;
    return r;
}

Vetor Vetor::operator -(const Vetor& v){
    Vetor r = *this;
    r.x = r.x - v.x;
    r.y = r.y - v.y;
    r.z = r.z - v.z;
    return r;
}

double Vetor::operator*(const Vetor& b){
    double prod;
    prod = x * b.x + y * b.y + z * b.z;
    return prod;
}

Vetor Vetor::operator*(const double b){
    Vetor r = *this;
    r.x = r.x * b;
    r.y = r.y * b;
    r.z = r.z * b;
    return r;
}

Vetor Vetor::operator%(const Vetor& b){
    Vetor r = *this;
    Vetor a = b;
    Vetor prod = r.ProdutoVetorial( a );

    return prod;
}

Vetor Vetor::ProdutoVetorial(Vetor &b){
    double xx, yy, zz;
    xx = y * b.z - b.y * z;
    yy = b.x * z - x * b.z;
    zz = x * b.y - b.x * y;

    Vetor prodVet = Vetor( xx, yy, zz );

    return prodVet;
}

Vetor Vetor::unitario(){
    double norma = Norma();
    double xx = x / norma;
    double yy = y / norma;
    double zz = z / norma;

    Vetor unit = Vetor( xx, yy, zz );

    return unit;
}
