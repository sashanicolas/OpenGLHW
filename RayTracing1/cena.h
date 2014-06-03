#ifndef CENA_H
#define	CENA_H

#include "Vetor.h"
#include "Geometria.h"
#include "luz.h"
#include <vector>

using namespace std;

class Cena {
public:
    Cena(Vetor& luzAmbiente, Vetor& corDeFundo,float kAmbiente);
    void setLuzAmbiente(Vetor& luzAmbiente);
    void setCorDeFundo(Vetor& corDeFundo);
    void addLuz(Luz* luz);
    void addGeometria(Geometria* obj);

    vector<Geometria*> geometrias;
    vector<Luz*> fLuz;
    Vetor luzAmbiente;
    float kLuzAmbiente;
    Vetor corDeFundo;
};

#endif	/*CENA_H */

