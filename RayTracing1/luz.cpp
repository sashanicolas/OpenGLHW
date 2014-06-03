#include "luz.h"
#include "Vetor.h"

Luz::Luz(){
}

Luz::~Luz(){
}

Luz::Luz(Vetor& posicao, Vetor& intensidade){
    this->posicao = posicao;
    this->intensidade = intensidade;
}
