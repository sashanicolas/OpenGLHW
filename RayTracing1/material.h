#ifndef MATERIAL_H
#define MATERIAL_H
#include "Vetor.h"

class material
{
    public:
        material(Vetor cor,float Ks,float kd,int shininess);
        material();
        virtual ~material();
        Vetor cor;
        float kspecular;
        float kdifusa;
        int shininess;
    protected:
    private:
};

#endif // MATERIAL_H
