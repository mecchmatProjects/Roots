# Roots - roots of polynomial

## References for root finding:

[Lobachevskiy](https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%9B%D0%BE%D0%B1%D0%B0%D1%87%D0%B5%D0%B2%D1%81%D0%BA%D0%BE%D0%B3%D0%BE_%E2%80%94_%D0%93%D1%80%D0%B5%D1%84%D1%84%D0%B5)

[Graeffe](https://en.wikipedia.org/wiki/Graeffe%27s_method)

[recent coolest: Jenkins-Traub ](https://en.wikipedia.org/wiki/Jenkins%E2%80%93Traub_algorithm)

[Jenkins-Traub for real numbers](https://www.researchgate.net/publication/242529401_A_Three-Stage_Algorithm_for_Real_Polynomials_Using_Quadratic_Iteration)

[others](https://en.wikipedia.org/wiki/Root-finding_algorithms)

[Sturm theory](https://en.wikipedia.org/wiki/Sturm%27s_theorem)

## Files:

The project contains header, source and test files for solution
of the Polinomial root problem solution.

Methods:

- Create/change polynome as array:

  setPoly(double* arr, size_t n);
 
- Set interval where root is seeked:

  setInterval(double a, double b);

- find one (maximal) root on interval:

  // name = Graeffe, Traub etc
  double findOneRoot_name(); 

- find N roots on interval:

  int findRoots_name(arr* roots, size_t N); // or return vector

TODO:
  a) complex roots

  b) complex coefficients of polynome


# Roots - optimization tasks
int allMax_Fib(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Golden-section_search

int allMax_GoldenSection(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Ternary_search
int allMax_Brent(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Brent%27s_method
int allMax_Newton(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Newton%27s_method_in_optimization

## References for optimization tasks:

Include file:
funcs.h

//https://en.wikipedia.org/wiki/Golden-section_search
//https://en.wikipedia.org/wiki/Ternary_search

//https://en.wikipedia.org/wiki/Brent%27s_method

//https://en.wikipedia.org/wiki/Newton%27s_method_in_optimization









