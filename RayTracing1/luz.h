#ifndef LUZ_H
#define	LUZ_H

#include "Vetor.h"
class Luz {
public:
    Luz();
    Luz(const Luz& orig);
    Luz(Vetor& posicao, Vetor& intensidade);
    virtual ~Luz();
    Vetor posicao;
    Vetor intensidade;
};

#endif	/* LUZ_H */
