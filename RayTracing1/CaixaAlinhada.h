#ifndef CAIXA_ALINHADA_H
#define	CAIXA_ALINHADA_H

#include "Vetor.h"
#include "Geometria.h"

class CaixaAlinhada : public Geometria {
public:

    CaixaAlinhada(Vetor& v1, Vetor& v2,material m);
    double intersecao(Raio& raio);
    Vetor getNormal(Vetor& ponto);

    Vetor normal;
    Vetor vertice2;
    Vetor vertice;
};

#endif	/* CAIXA_ALINHADA_H */

