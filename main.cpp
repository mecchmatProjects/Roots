#include "RootSeeker.h"
#include "Polynom.h"
#include <ctime>
#include <random>


#define RAND_MAX 10000

double randomDouble(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double* randomArray(int n)
{
   double* randArray;
   randArray = new double[n];
   for(int i = 0; i < n; i++)
   {
      randArray[i]= randomDouble(-100, 100);
   }
   return randArray;
}

Polynom randomPoly(int maxDegree)
{
    double *roots;
    int n;

    while (true)
    {
        n = rand() % maxDegree;
        if (n != 0)
        {
            break;
        }
    }

    roots = randomArray(n);
    cout << "Roots: ";
    for (int i = 0; i < n; i++)
    {
        cout << roots[i] << " ";
    }
    cout << "\n";

    Polynom dvochlen, p;
    dvochlen.degree = 1;
    dvochlen.koef = new double[2];
    dvochlen.koef[1] = 1;

    dvochlen.koef[0] = - roots[0];
    p = dvochlen;
    for (int i = 1; i < n; i++)
    {
        dvochlen.koef[0] = - roots[i];
        p = p*dvochlen;
    }

    return p;

}


// Input Polynomial: {1, 2, 3, 4} -> 4x^3 + 3x^2 + 2x + 1

int main()
{
    //   Test 1. Generate random the polynomials by their roots
    cout << "\nTEST 1\n\n";

    Polynom p;
    srand(time(NULL));

    int tests = 10;
    int maxDegree = 5;

    cout << "-------------------------------------------------------------------------\n";
    for (int i = 0; i < tests; i++)
    {
        p = randomPoly(maxDegree);

        cout << "Polynom: ";
        p.printPoly();
        cout << "\n";

        RootSeeker rs1;
        rs1.SetInterval(-600, 600);

        rs1.SetPoly(p);

        rs1.countOfRoots();

        cout << "(Newton Method) ";
        rs1.findRoots(rs1.findOneRoot_Newton);
        rs1.printRoots();

        cout << "(Lobachevskiy Method) ";
        rs1.findRoots(rs1.findOneRoot_Lobachevskiy);
        rs1.printRoots();

        cout << "(False Position Method) ";
        rs1.findRoots(rs1.findOneRoot_FalsePosition);
        rs1.printRoots();
        cout << "-------------------------------------------------------------------------\n";
    }




    /*
    //   Test 2. Find roots of the polynomials (1, 2 and 3 orders)

    cout << "\n\n\n\n\n\n\n\n\n TEST 2\n\n"

    RootSeeker rs;
    rs.SetInterval(-100, 100);

    cout << "1st order\n";
    double test_poly[][2] ={{5,1}, {-1,2}, {4,2}, {0,2}, {2,0} ,{0,0}};
    double roots_poly[6] = {-5, 0.5, -2, 0, NOROOT, NOROOT};
    for(int i=0; i<6;++i)
    {
        rs.SetPoly(1, test_poly[i]);
        rs.printPoly();

        cout << "Root: ";
        if (roots_poly[i] == NOROOT)
        {
            cout << "No root\n";
        }
        else
        {
            cout << roots_poly[i] << "\n";
        }

        rs.countOfRoots();

        cout << "(Lobachevskiy Method) ";
        rs.findRoots(rs.findOneRoot_Lobachevskiy);
        rs.printRoots();

        cout << "(Newton Method) ";
        rs.findRoots(rs.findOneRoot_Newton);
        rs.printRoots();

        cout << "(False Position Method) ";
        rs.findRoots(rs.findOneRoot_FalsePosition);
        rs.printRoots();
        cout << "\n";

    }
    cout << "-------------------------------------------------------------------------\n";


    cout << "2nd order\n";
    double test_poly2[][3] = {{1.,-3.,2.0}, {1.,-2.,1}, {2.,4, -6.}, {1,1,1}, {2,0,-4} ,{3,0,9},{0.,-3.,2.0}, {0.,-2.,1}, {0.,0., 4.}, {0,2,4}, {0,0,0} ,{3,0,0}, {-1, 0, 1}};
    double roots_poly2[][2] = {{1, 0.5}, {1, 1}, {1, -1.0/3}, {NOROOT, NOROOT}, {sqrt(0.5), -sqrt(0.5)}, {NOROOT, NOROOT}, {0, 1.5}, {0, 2},{0, 0}, {0, -0.5}, {NOROOT, NOROOT}, {NOROOT, NOROOT}, {-1, 1}};
    for(int i=0; i<13;++i)
    {
        rs.SetPoly(2, test_poly2[i]);
        rs.printPoly();

        cout << "Roots: ";
        if (roots_poly2[i][0] == NOROOT && roots_poly2[i][1] == NOROOT)
        {
            cout << "No roots\n";
        }
        else
        {
            cout << roots_poly2[i][0] << " " << roots_poly2[i][1] << "\n";
        }

        rs.countOfRoots();

        cout << "(Lobachevskiy Method) ";
        rs.findRoots(rs.findOneRoot_Lobachevskiy);
        rs.printRoots();

        cout << "(Newton Method) ";
        rs.findRoots(rs.findOneRoot_Newton);
        rs.printRoots();

        cout << "(False Position Method) ";
        rs.findRoots(rs.findOneRoot_FalsePosition);
        rs.printRoots();
        cout << "\n";


    }
    cout << "-------------------------------------------------------------------------\n";


    cout << "3d order\n";
    double test_poly3[][4] = {{0, -3, 2, 1}, {1, 2, 1, 0}, {56, -34, 1, 1}, {0, 1, 0, 1}, {1, 0, 0, 1}, {-6, 2, -1, -4}};
    double roots_poly3[][3] = {{0, 1, -3}, {-1, -1, NOROOT}, {-7, 4, 2}, {0, NOROOT, NOROOT}, {NOROOT, NOROOT, -1}, {NOROOT, NOROOT, -1.38835}};
    for(int i=0; i<6;++i)
    {
        rs.SetPoly(3, test_poly3[i]);
        rs.printPoly();

        cout << "Roots: ";
        if (roots_poly3[i][0] == NOROOT && roots_poly3[i][1] == NOROOT && roots_poly3[i][2] == NOROOT)
        {
            cout << "No roots\n";
        }
        else
        {
            cout << roots_poly3[i][0] << " " << roots_poly3[i][1] << " " << roots_poly3[i][2] << "\n";
        }

        rs.countOfRoots();

        cout << "(Lobachevskiy Method) ";
        rs.findRoots(rs.findOneRoot_Lobachevskiy);
        rs.printRoots();

        cout << "(Newton Method) ";
        rs.findRoots(rs.findOneRoot_Newton);
        rs.printRoots();

        cout << "(False Position Method) ";
        rs.findRoots(rs.findOneRoot_FalsePosition);
        rs.printRoots();
        cout << "\n";

    }



    //   Test 3. Generate random polynomials and calculate time work of the methods

    cout << "\n\n\n\n\n\n\n\n\n TEST 3\n\n"

    double t1 = 0;
    double t2 = 0;
    double t3 = 0;
    double *ar;
    for (int i = 0; i < 100; i++)
    {
        int n = rand() % 15;
        if (n == 0)
        {
            continue;
        }

        ar = new double[n];
        ar = randomArray(n);
        rs.SetPoly(n - 1, ar);

        rs.countOfRoots();

        clock_t StartT1 = clock();
        rs.findRoots(rs.findOneRoot_Newton);
        clock_t EndT1 = clock();
        t1 += (EndT1 - StartT1) / (double) CLOCKS_PER_SEC;

        clock_t StartT2 = clock();
        rs.findRoots(rs.findOneRoot_Lobachevskiy);
        clock_t EndT2 = clock();
        t2 += (EndT2 - StartT2) / (double) CLOCKS_PER_SEC;

        clock_t StartT3 = clock();
        rs.findRoots(rs.findOneRoot_FalsePosition);
        clock_t EndT3 = clock();
        t3 += (EndT3 - StartT3) / (double) CLOCKS_PER_SEC;

        delete[] ar;

    }

    cout << "\n";
    cout << "Newton: " << t1 << " seconds\n";
    cout << "Lobachevskiy: " << t2 << " seconds\n";
    cout << "False Position: " << t3 << " seconds\n";
    */
}
