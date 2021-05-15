#include "RootSeeker.h"

void RootSeeker::SetPoly(int d, double *coefs)
{
    p.deletePoly();

    int degr = d;
    for (int i = degr; i > 0; i--)
    {
        if (coefs[i] == 0)
        {
            d--;
        }
        else
        {
            break;
        }
    }
    if (d == 0)
    {
        cout << "Your polynom is incorrect\n";
        correctPoly = false;
        p.SetPoly(degr, coefs);
    }
    else
    {
        correctPoly = true;
        p.SetPoly(d, coefs);
    }
}

void RootSeeker::printPoly()
{
    p.printPoly();
}

void RootSeeker::SetInterval(double a, double b)
{
    this->a = a;
    this->b = b;
}

void RootSeeker::countOfRoots()
{
    if (!correctPoly)
    {
        return;
    }

    // Sturm's theorem

    Polynom *hi;
    hi = new Polynom[p.degree + 1];
    hi[0] = p;
    hi[1] = p.derivative();

    for (int i = 2; i <= p.degree; i++)
    {
        hi[i] = hi[i - 2]%hi[i - 1];
        for (int j = 0; j <= hi[i].degree; j++)
        {
            hi[i].koef[j] *= -1;
        }
    }

    int c1, c2;
    double y1, y2, y3, y4;
    c1 = 0;
    c2 = 0;
    y1 = hi[0].value(a);
    y3 = hi[0].value(b);

    for (int i = 1; i <= p.degree; i++)
    {

        y2 = hi[i].value(a);
        y4 = hi[i].value(b);

        if ( !((y1 > 0 && y2 > 0) ||(y1 < 0 && y2 < 0)) )
        {
            c1++;
        }
        if ( !((y3 > 0 && y4 > 0) ||(y3 < 0 && y4 < 0)) )
        {
            c2++;
        }

        y1 = y2;
        y3 = y4;
    }

    this->cr = c1 - c2;
    cout << "Counts of the real roots on interval [" << a << ", " << b << "]: " << this->cr << "\n";
    roots = new double[cr];
}

double RootSeeker::findOneRoot_Lobachevskiy(Polynom &poly, double left, double right)
{
    poly.removeMultipleRoots();
    poly.deleteBy_a0();

    double x;

    // if poly such as x^n + an, (a1, a2, a3, a4, ..., an-1 = 0) then Lobachevskiy will not work
    bool check = 1;
    for (int i = 1; i < poly.degree; i++)
    {
        if (poly.koef[i] != 0)
        {
            check = 0;
            break;
        }
    }
    if (check)
    {
        if (poly.koef[0] > 0 && poly.degree%2 == 0)
        {
            return NOROOT;
        }
        else
        {
            x = powl(fabs(poly.koef[0]), 1.0/poly.degree);
        }
    }
    else
    {
        int N = poly.degree;
        int N1 = N + 1;
        mpf_class b[N1], c[N1];
        for (int i = 0; i < N1; i++)
        {
            b[i] = poly.koef[N1 - 1 - i];
            c[i] = 0;
        }

        bool brk;
        int st = 0;
        while (true)
        {
            brk = 1;

            // create a new polynomial
            c[0] = b[0]*b[0];
            c[N1 - 1] = b[N1 - 1]*b[N1 - 1];
            int z, i;
            for (int k = 1; k < N1 - 1; k++)
            {
                i = 1;
                z = -2;
                c[k] += b[k]*b[k];
                while (true)
                {
                    c[k] += z*b[k - i]*b[k + i];
                    if ((k - i == 0) || (k + i == N1 - 1))
                    {
                        break;
                    }
                    i++;
                    z *= -1;
                }
            }

            // if c[i] = b[i]^2 or count of the iterations > 10 then break
            for (int i = 0; i < N1; i++)
            {
                if (abs(abs(c[i]) - b[i]*b[i]) > EPSILON)
                {
                    brk = 0;
                    break;
                }
            }
            if (brk)
            {
                break;
            }

            st++;
            if (st > 10)
            {
                break;
            }

            // update coefficients
            for (int i = 0; i < N1; i++)
            {
                b[i] = c[i];
                c[i] = 0;
            }

        }

        // calculate root
        mpf_class x_;
        for (int i = 1; i < N1; i++)
        {
            if (b[i - 1] == 0)
            {
                continue;
            }

            x_ = abs(b[i]/b[i - 1]);

            for (int j = 0; j < st; j++)
            {
                {
                    x_ = sqrt(x_);
                }
            }

            if (fabs(poly.value(x_.get_d())) < EPSILON || fabs(poly.value(- x_.get_d())) < EPSILON)
            {
                break;
            }


        }
        x = x_.get_d();
    }

    // determine the sign of root
    if (fabs(poly.value(x)) > EPSILON)
    {
        x *= -1;
    }

    return x;
}

double RootSeeker::findOneRoot_FalsePosition(Polynom &poly, double left, double right)
{
    double a = left;
    double b = right;
    double c = (a*poly.value(b) - b*poly.value(a))/(poly.value(b) - poly.value(a));

    int i = 0;
    while (fabs(poly.value(a)) > EPSILON)
    {
        if (poly.value(c) < EPSILON)
        {
            a = c;
        }
        else
        {
            b = c;
        }

        c = (a*poly.value(b) - b*poly.value(a))/(poly.value(b) - poly.value(a));


        i++;
        if (i > 10000)
        {
            cout << "This method doesn't work for this polynom\n";
            return NOROOT;
        }
    }

    return a;
}

double RootSeeker::findOneRoot_Newton(Polynom &poly, double left, double right)
{
    Polynom pd = poly.derivative();

    double x0 = (left + right)/2;
    if (x0 == 0)
    {
        x0 = (left + right)/2;
        if (x0 == 0)
        {
            x0 -= 5;
        }
    }

    double xn = x0 - poly.value(x0)/pd.value(x0);

    while (fabs(xn - x0)> EPSILON)
    {
        x0 = xn;
        xn = xn - poly.value(xn)/pd.value(xn);
    }

    return xn;
}


void RootSeeker::findRoots(double (*methodName)(Polynom&, double, double))
{
    if (!correctPoly || cr == 0)
    {
        return;
    }

    Polynom dvochlen;
    dvochlen.degree = 1;
    dvochlen.koef = new double[2];
    dvochlen.koef[1] = 1;

    Polynom cop;
    p.copyPoly(cop);
    roots[0] = methodName(cop, a, b);

    if (fabs(roots[0]) < EPSILON)
    {
        roots[0] = 0;
    }

    if (roots[0] == NOROOT)
    {
        return;
    }

    dvochlen.koef[0] = - roots[0];

    for (int i = 1; i < cr; i++)
    {
        cop = cop/dvochlen;

        roots[i] = methodName(cop, a, b);

        if (roots[i] == NOROOT)
        {
            return;
        }

        if (fabs(roots[i]) < EPSILON)
        {
            roots[i] = 0;
        }

        dvochlen.koef[0] = - roots[i];
    }

}

void RootSeeker::printRoots()
{
    if (correctPoly && cr != 0 && roots[0] != NOROOT)
    {
        cout << "Roots: ";
        for (int i = 0; i < cr; i++)
        {
            cout << roots[i] << " ";
        }
        cout << "\n";
    }
    else
    {
        cout << "No roots\n";
    }
}

double* RootSeeker::getRoots()
{
    return roots;
}


