#include "CaixaAlinhada.h"
#include <iostream>
using namespace std;

CaixaAlinhada::CaixaAlinhada(Vetor& v1, Vetor& v2,material m) : Geometria(m){
    vertice = v1;
    vertice2 = v2;
}

Vetor CaixaAlinhada::getNormal(Vetor& ponto){
    return normal;
}

double CaixaAlinhada::intersecao(Raio& raio){
    double xMin = vertice.x;
    double yMin = vertice.y;
    double zMin = vertice.z;

    double xMax = vertice2.x;
    double yMax = vertice2.y;
    double zMax = vertice2.z;

    Vetor ponto;
    double t;

    if ( raio.dir.x > 0 ){
        t = (xMin - raio.origem.x) / raio.dir.x;
        ponto = raio.origem + raio.dir*t;
        if ( ponto.y >= yMin && ponto.y <= yMax && ponto.z >= zMin && ponto.z <= zMax ){
            normal = Vetor( -1, 0, 0 );
            return t;
        }
    }else{
        t = (xMax - raio.origem.x) / raio.dir.x;
        ponto = raio.origem + raio.dir*t;
        if ( ponto.y >= yMin && ponto.y <= yMax && ponto.z >= zMin && ponto.z <= zMax ){
            normal = Vetor( 1, 0, 0 );
            return t;
        }
    }

    if ( raio.dir.y < 0 ){
        t = (yMax - raio.origem.y) / raio.dir.y;
        ponto = raio.origem + raio.dir*t;
        if ( ponto.x >= xMin && ponto.x <= xMax && ponto.z >= zMin && ponto.z <= zMax ){
            normal = Vetor( 0, 1, 0 );
            return t;
        }
    } else {
        t = (yMin - raio.origem.y) / raio.dir.y;
        ponto = raio.origem + raio.dir*t;
        if ( ponto.x >= xMin && ponto.x <= xMax && ponto.z >= zMin && ponto.z <= zMax ){
            normal = Vetor( 0, -1, 0 );
            return t;
        }
    }

    if ( raio.dir.z < 0 ){
        t = (zMax - raio.origem.z) / raio.dir.z;
        ponto = raio.origem + raio.dir*t;
        if ( ponto.x >= xMin && ponto.x <= xMax && ponto.y >= yMin && ponto.y <= yMax ){
            normal = Vetor( 0, 0, 1 );
            return t;
        }
    } else {
        t = (zMin - raio.origem.z) / raio.dir.z;
        ponto = raio.origem + raio.dir*t;
        if ( ponto.x >= xMin && ponto.x <= xMax && ponto.y >= yMin && ponto.y <= yMax ){
            normal = Vetor( 0, 0, -1 );
            return t;
        }
    }
    return -1;
}
