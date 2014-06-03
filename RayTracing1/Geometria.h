#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "Vetor.h"
#include "raio.h"
#include "material.h"

class Geometria {
public:
    Geometria(material materialObj);
    virtual ~Geometria();
    virtual double intersecao(Raio& r) = 0;
    virtual Vetor getNormal(Vetor& ponto) = 0;
    material materialObj;
};

#endif	/* GEOMETRIA_H */

