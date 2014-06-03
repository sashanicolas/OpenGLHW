#ifndef ESFERA_H
#define	ESFERA_H

#include "Geometria.h"

class Esfera : public Geometria {
public:
    Esfera(material m);
    Esfera(Vetor& centro, double raio,material m);
    virtual ~Esfera();
    double intersecao(Raio& r);
    Vetor getNormal(Vetor& ponto);
    Vetor centro;
    double raio;
};

#endif	/* ESFERA_H */
