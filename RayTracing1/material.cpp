#include "material.h"
#include "Vetor.h"

material::material(Vetor cor,float ks,float kd,int shininess){
    this->cor = cor; ///cor do material
    this->kspecular = ks; ///coeficiente de reflexão especular
    this->kdifusa = kd; ///coeficiente da componente difusa
    this->shininess = shininess; ///shiness do material para componente especular
}

material::material(){

}

material::~material(){

}
