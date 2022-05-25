#include <iostream>
#include <inttypes.h>
#include <cinttypes>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include "ChainHandlers.h"

typedef double TDBL ;

class GoldenSectionHandler : public AbstractHandler {
 public:
  std::vector< double > Handle(std::string request, double (*f)(double), TDBL a, TDBL b, std::vector< double > mins) override {
    if (request == "GoldenSelection") {
        std::vector< double > results;
        for(int i = 0; i < mins.size()-1; i++) {
            results.push_back(this->calculate(f, mins[i], mins[i+1]));
        }
        return results;
    } else {
      return AbstractHandler::Handle(request, f, a, b, mins);
    }
  }
  
  double calculate(double (*f)(double), TDBL a, TDBL b) {
    double gr = (sqrt(5) + 1) / 2;
    double c = b - (b - a) / gr;
    double d = a + (b - a) / gr;
    
    while (abs(b - a) > (1e-5)){
       if(f(c) < f(d)) {
            b = d;
        } else {
            a = c;
        }
        
        c = b - (b - a) / gr;
        d = a + (b - a) / gr;
    }
    
    return (b + a) / 2;
  }
};


class BrentHandler : public AbstractHandler {
 public:
  std::vector< double > Handle(std::string request, double (*f)(double), TDBL a, TDBL b, std::vector< double > mins) override {
    if (request == "Brent") {
        std::vector< double > results;
        for(int i = 0; i < mins.size()-1; i++) {
            results.push_back(this->calculate(f, mins[i], mins[i+1]));
        }
        return results;
    } else {
      return AbstractHandler::Handle(request, f, a, b, mins);
    }
  }
  
  double calculate(double (*f)(double), TDBL a, TDBL b) {
    double fa = f(a);
    double fb = f(b);
    
    //if((fa * fb) >= 0) {
    //    return 0;
    //}
    
    if(abs(fa) < abs(fb)) {
        std::swap(a,b);
    }
    
    double c = a;
    bool flag = true;
    double s = 0;
    double d;
    while( (f(b) != 0) || (f(s) != 0) || (abs(b - a) > (1e-5))) {
        
        if((f(a) != f(c)) && (f(b) != f(c))) {
            
            s = ((a*f(b)*f(c)) / ((f(a) - f(b))*(f(a) - f(c)))) + ((b*f(a)*f(c)) / ((f(b) - f(a))*(f(b) - f(c)))) + ((c*f(a)*f(b)) / ((f(c) - f(a))*(f(c) - f(b))));
        } else {
            s = b - (f(b)*((b - a) / (f(b) - f(a))));
        }
        
        double smaller = (3 * a + b) / 4;
        double bigger = b;
        
        if(smaller > bigger) {
            std::swap(smaller, bigger);
        }
        
        if( !(s > smaller && s < bigger) || 
            (flag == true && (abs(s-b) >= abs(b-c) / 2)) ||
            (flag == false && (abs(s-b) >= abs(b-c) / 2)) ||
            (flag == true && (abs(b-c) < (1e-5))) ||
            (flag == false && (abs(c-d) < (1e-5)))
        ) {
            
            s =  (a + b) / 2;
            flag = true;
        } else {
            flag = false;
        }
        
        d = c;
        c = b;
        
        if(f(a) * f(s) < 0) {
            
            b = s;
        } else {
            
            a = s;
        }
        
        if(abs(f(a)) < abs(f(b))) {
            std::swap(a, b);
        }
        
    }
    
    return b;
  }
};


class TernarySearchHandler : public AbstractHandler {
 public:
  std::vector< double > Handle(std::string request, double (*f)(double), TDBL a, TDBL b, std::vector< double > mins) override {
    if (request == "TernarySearch") {
        std::vector< double > results;
        for(int i = 0; i < mins.size()-1; i++) {
            results.push_back(this->calculate(f, mins[i], mins[i+1]));
        }
        return results;
    } else {
      return AbstractHandler::Handle(request, f, a, b, mins);
    }
  }
  
  double calculate(double (*f)(double), TDBL a, TDBL b) {
    
    if(abs(b - a) < (1e-5)) {
        return (a + b) / 2;
    }
    
    double a_third = (2*a + b) / 3;
    double b_third = (a + 2*b) / 3;
    
    if(f(a_third) > f(b_third)) {
        return this->calculate(f, a_third, b);
    } else {
        return this->calculate(f, a, b_third);
    }
  }
};