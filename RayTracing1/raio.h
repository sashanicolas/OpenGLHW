#ifndef RAIO_H
#define	RAIO_H

#include "Vetor.h"

class Raio {
public:
    Raio(Vetor& origem, Vetor& dir);
    Vetor origem;
    Vetor dir;
};

#endif	/* RAIO_H */

