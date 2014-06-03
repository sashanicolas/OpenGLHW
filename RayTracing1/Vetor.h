#ifndef VETOR_H
#define	VETOR_H

class Vetor {
public:
    Vetor();
    Vetor(double x, double y, double z);
    Vetor(const Vetor& orig);
    virtual ~Vetor();
    double Norma();
    Vetor operator+(const Vetor& v);
    Vetor operator-(const Vetor& v);
    double operator*(const Vetor& b);
    Vetor operator%(const Vetor& b);
    Vetor operator*(const double b);
    Vetor ProdutoVetorial(Vetor &b);
    Vetor unitario();

    double x, y, z;
};

#endif	/* VETOR_H */

