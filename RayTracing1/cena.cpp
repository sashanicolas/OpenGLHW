#include <vector>
#include "Vetor.h"
#include "cena.h"

using namespace std;

Cena::Cena(Vetor& luzAmbiente, Vetor& corDeFundo,float kAmbiente){
    this->luzAmbiente = luzAmbiente;
    this->corDeFundo = corDeFundo;
    this->kLuzAmbiente = kAmbiente;
}

void Cena::setLuzAmbiente(Vetor& luzAmbiente){
    this->luzAmbiente = luzAmbiente;
}

void Cena::setCorDeFundo(Vetor& corDeFundo){
    this->corDeFundo = corDeFundo;
}

void Cena::addLuz(Luz* luz){
    this->fLuz.push_back( luz );
}

void Cena::addGeometria(Geometria* obj){
    this->geometrias.push_back( obj );
}
