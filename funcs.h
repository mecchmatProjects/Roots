#ifndef __FUNCS__
#define __FUNCS__

#include <cinttypes>


typedef TDBL double;

TDBL (*RealFunc)(TDBL);

/*
  Fibonacci method min for single extremum function
  @args - f (POINTER) - R1->R1 function
  @args - a(double) - left side of interval
  @args - b(double) - right side of interval
  @result - value where is minimum	 
*/
TDBL singleMin_Fib(RealFunc f, TDBL a, TDBL b);

TDBL singleMax_Fib(RealFunc f, TDBL a, TDBL b);

/*
  Fibonacci method min for multiple extremum function
  @args - f (POINTER) - R1->R1 function
  @args - a(double) - left side of interval
  @args - b(double) - right side of interval
  @args - (out) mins - pointer to array of extremums 
  @result - number of extremums	 
*/
int allMin_Fib(RealFunc f, TDBL a, TDBL b, TDBL* mins);

int allMax_Fib(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Golden-section_search

int allMax_GoldenSection(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Ternary_search
int allMax_Brent(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Brent%27s_method
int allMax_Newton(RealFunc f, TDBL a, TDBL b, TDBL* mins);
//https://en.wikipedia.org/wiki/Newton%27s_method_in_optimization

//Random walk? genetic?

#endif // __FUNCS__
