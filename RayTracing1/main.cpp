#include <math.h>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

#include "cena.h"
#include "Vetor.h"
#include "Camera.h"
#include "Geometria.h"
#include "esfera.h"
#include "CaixaAlinhada.h"
#include "luz.h"
#include "material.h"

#define INFINITO 9999999
#define max(A,B) A>B?A:B

using namespace cv;
using namespace std;

double windowWidth=700,
        windowHeight=700;

Cena *cena;
vector<Geometria*> geometrias;
vector<Luz*> fLuz;

Vetor eye(100, 40, 40),
      center(0, 0, 0),
      up(0, 1, 0);
Camera cam(eye, center, up, 90, 30, 100, windowWidth, windowHeight);

Vetor RayTrace(Raio& raio);

void LuzAmbiente(float * cor){
    Vetor cAmbiente = cena->luzAmbiente;
    float kAmbiente = cena->kLuzAmbiente;
    cor[0] += kAmbiente * cAmbiente.x;
    cor[1] += kAmbiente * cAmbiente.y;
    cor[2] += kAmbiente * cAmbiente.z;
}

void LuzDifusa(float * cor, double kd, double NdotL,int idFonte){

    Vetor rgbLuz = cena->fLuz[idFonte]->intensidade;

    float r = kd * rgbLuz.x * NdotL;
    float g = kd * rgbLuz.y * NdotL;
    float b = kd * rgbLuz.z * NdotL;
    cor[0] += r;
    cor[1] += g;
    cor[2] += b;
}

void LuzEspecular(float * cor, double ks, double HdotN, int shininess, int idFonte){

    Vetor rgbLuz = cena->fLuz[idFonte]->intensidade;

    HdotN = pow( HdotN, shininess );
    float r = ks * rgbLuz.x * HdotN;
    float g = ks * rgbLuz.y * HdotN;
    float b = ks * rgbLuz.z * HdotN;
    cor[0] += r;
    cor[1] += g;
    cor[2] += b;
}

Vetor shade(Raio& raio, Geometria* obj, Vetor& pontoIntersecao, Vetor& normal){
    ///Componentes Ambiente, Difusa e Especular
    float cAmbiente[3] = {0.0},
           cDifusa[3] = {0.0},
           cEspecular[3] = {0.0};

    LuzAmbiente(cAmbiente); ///Obtém a componente ambiente
    ///Características do material
    float kd = obj->materialObj.kdifusa;
    float ks = obj->materialObj.kspecular;
    int shininess = obj->materialObj.shininess;

    float t = -INFINITO;
    for ( unsigned i = 0; i < cena->fLuz.size( ); i++ ){
        Vetor dirLuz = cena->fLuz[i]->posicao - pontoIntersecao;
        Raio raioDirLuz( pontoIntersecao, dirLuz );

        ///Sombra
         for ( unsigned j = 0; j < cena->geometrias.size( ); j++ ){
            t = cena->geometrias[j]->intersecao( raioDirLuz );
            if ( t > 0.001 ){
                break;
            }
        }

        if ( t <= 0 ){ ///Não tem sombra

            ///Vetor direção da Luz
            Vetor dirLuz = cena->fLuz[i]->posicao - pontoIntersecao;
            dirLuz = dirLuz.unitario( );

            double NdotL = dirLuz * normal;

            LuzDifusa(cDifusa, kd, NdotL, i);

            ///Vetor direção do olho
            Vetor dirEye = raio.origem - pontoIntersecao;
            dirEye = dirEye.unitario( );

            Vetor halfVector = dirEye + dirLuz;
            halfVector = halfVector.unitario();
            double HdotN = halfVector*normal;

            LuzEspecular(cEspecular, ks, HdotN , shininess, i);
        }
    }

    Vetor corObj = obj->materialObj.cor;

    cAmbiente[0] = cAmbiente[0] * corObj.x;
    cAmbiente[1] = cAmbiente[1] * corObj.y;
    cAmbiente[2] = cAmbiente[2] * corObj.z;

    cDifusa[0] = cDifusa[0] * corObj.x;
    cDifusa[1] = cDifusa[1] * corObj.y;
    cDifusa[2] = cDifusa[2] * corObj.z;

    cEspecular[0] = cEspecular[0];
    cEspecular[1] = cEspecular[1];
    cEspecular[2] = cEspecular[2];

    Vetor rgb( cAmbiente[0] + cDifusa[0] + cEspecular[0], cAmbiente[1] + cDifusa[1] + cEspecular[1], cAmbiente[2] + cDifusa[2] + cEspecular[2] );

    return rgb;
}

Vetor RayTrace(Raio& raio){
    Vetor pontoIntersecao;
    Vetor normal;
    Vetor cor;
    double tmin = INFINITO;
    double t = -INFINITO;
    int objetoIntercepta = -1;

    for (unsigned i=0; i<cena->geometrias.size(); i++ ){
        t = cena->geometrias[i]->intersecao(raio);
        if ( t > 0.01 ){
            if ( t < tmin ){ ///Pega o objeto mais perto da câmera
                tmin = t;
                objetoIntercepta = i;
            }
        }
    }
    if ( tmin < 0 || tmin == INFINITO ){
        Vetor fundo(0.5,0.5,0.5);
        cor = fundo;
        return cor;
    }else{
        pontoIntersecao = raio.origem + raio.dir * tmin; ///Equação paramétrica
        normal = cena->geometrias[objetoIntercepta]->getNormal( pontoIntersecao );
        cor = shade( raio, cena->geometrias[objetoIntercepta], pontoIntersecao, normal);
        return cor;
    }
}

void display(){
    Mat img(windowHeight,windowWidth,CV_8UC3);
    Vetor rgb;
    for (double i=0; i<=windowWidth; i++ ){
        for (double j=0; j <= windowHeight; j++ ){
            Raio raio = cam.getRaio(i,j);
            rgb = RayTrace(raio);
            img.at<Vec3b>(windowHeight - j,i) = Vec3b(255*rgb.z,255*rgb.y,255*rgb.x);
        }
    }
    cvNamedWindow("RayTracing");
    imshow("RayTracing",img);
    imwrite("output.jpg",img);
    cvWaitKey(0);
}

void init(){
    ///Inicializa a cena descrita no slide da aula
    Vetor posLuz( 60, 120, 40 );
    Vetor intensidadeLuz( 1, 1, 1 );
    Luz *luz = new Luz( posLuz, intensidadeLuz );

    fLuz.push_back( luz );

    Vetor cor = Vetor( 0, 0.0, 1);
    material m1(cor,0.3,0.3, 20);

    Vetor centroEsfera = Vetor( 0, 20, 0 );
    Esfera *esfera;
    esfera = new Esfera( centroEsfera, 25 ,m1 );

    //caixa alinhada 1
    cor = Vetor( 0.7, 0.7, 0.0);
    material m2(cor,0.3,0.3,3.0);

    Vetor p1( -80, -50, -50 );
    Vetor p2( 50, -45, 50 );

    CaixaAlinhada *caixaHorizontal = new CaixaAlinhada( p1, p2 ,m2);

    //caixa alinhada 2
    cor = Vetor( 0.7, 0.7, 0.0);
    material m3(cor,0.3,0.3, 3.0);

    Vetor p3( -80, -50, -60 );
    Vetor p4( 50, 50, -50 );
    CaixaAlinhada *caixaVertical = new CaixaAlinhada( p3, p4 ,m3);

    geometrias.push_back( esfera );
    geometrias.push_back( caixaHorizontal );
    geometrias.push_back( caixaVertical );

    Vetor corFundo(0.5, 0.5, 0.5);
    Vetor luzAmb( 1, 1, 1 );
    float kAmbiente = 0.3;
    cena = new Cena(luzAmb,corFundo,kAmbiente);

    for ( unsigned i = 0; i < fLuz.size( ); i++ ){
        cena->addLuz( fLuz[i] );
    }

    for ( unsigned i = 0; i < geometrias.size( ); i++ ){
        cena->addGeometria(geometrias[i]);
    }
}

int main(int argc, char** argv){
    init( );
    display();
}
