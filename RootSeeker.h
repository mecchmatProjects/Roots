/*
The MIT License (MIT)

Copyright (c) 2021 Viktor Borodin (borodin@mail.univ.kiev.ua) and


This module is designed for equation solving to support basic math into the project.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __ROOT_SEEKER__
#define __ROOT_SEEKER__

/* Deal with C++ */
#ifdef __cplusplus
	extern "C" {
#endif

//#define _DBL_TYPE_MATH_
//#define _RATIO_TYPE_MATH_
#define _DBL_ERROR 0.0001


#include <stdio.h>
#include <stdlib.h>

// or as a class in C++
typdef struct RootSeeker{

    //private
    double* coef;
    size_t n;

    double a;
    double b;

    double* roots;
    size_t root_num;
} RootSeeker;

   //methods:
  extern int setPoly(RootSeeker* rs, const double* a, size_t n);

   //***

 extern double findOneRoot_Gaeffe(const RootSeeker* rs);
   
  // return actual number of real roots
 extern int findRoots_Gaeffe(const RootSeeker* rs, double* res, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* __ROOT_SEEKER__ */
