#include "Polynom.h"
#include <gmpxx.h>

#define NOROOT 11111111111
#define EPSILON 0.00000001

class RootSeeker
{
private:
    double *roots;
    Polynom p;
    double a, b;
    int cr; // counts of roots
    bool correctPoly;

public:
    RootSeeker(){};

    void SetPoly(int d, double *coef);
    void SetPoly(Polynom poly);
    void printPoly();
    void SetInterval(double a, double b);
    void countOfRoots();
    double* getRoots();
    void printRoots();

    static double findOneRoot_FalsePosition(Polynom &poly, double left, double right);
    static double findOneRoot_Newton(Polynom &poly, double left, double right);
    static double findOneRoot_Lobachevskiy(Polynom &poly, double left, double right);

    void findRoots(double (*methodName)(Polynom&, double, double));


};

