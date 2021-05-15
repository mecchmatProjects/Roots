
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
#include <cstring>
#include <cstdlib>

#ifndef POLYNOM_H
#define POLYNOM_H

class Polynom
{
public:
    int degree;
    double *koef;

    Polynom();
    Polynom(int d, double *k);
    ~Polynom();
    void deletePoly();

    void SetPoly(int d, double *k);
    void copyPoly(Polynom &ob);
    Polynom operator/(Polynom &ob);
    Polynom operator%(Polynom &ob);
    Polynom& operator=(const Polynom &ob);
    void printPoly();
    void deleteBy_a0();
    Polynom derivative();
    double value(double x);
    void removeMultipleRoots(void);
};
#endif
