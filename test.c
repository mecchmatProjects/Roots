
#include<stdio.h>

#include <time.h> // measure performance

#include "RootSeeker.h"



int main(){


   // primary tests

   // 1st order
   double test_poly[][2] ={ {1.,1.}, {1.,2.}, {4.,2.}, {0,2}, {2,0} ,{0,0}
    };

   double test_root[] ={ {1.}, {0.5}, {2.}, {0}, {NOROOT} ,{NOROOT}
    };

   RootSeeker rs;
   for(int i=0; i<6;++i){
       int r = setPoly(&rs,test_poly[i],2);
       if(r!=SUCCESS) {
          // TODO: more informative message
          fprintf(stderr,"can\'t initialize polynome");
          break;
       }        
       double root  = findOneRoot_Gaeffe(&st);
  
      if(!isEqual(root,test_root[i])){
     	fprintf(stdout,"test %d fail: root = %lf, test_root=%lf", i, root, test_root[i]);
      }

   }

 // 2nd order
   double test_poly2[][3] ={ {1.,-3.,2.0}, {1.,-2.,1}, {2.,4, -6.}, {1,1,1}, {2,0,-4} ,{3,0,9}
             {0.,-3.,2.0}, {0.,-2.,1}, {0.,0., 4.}, {0,2,4}, {0,0,0} ,{3,0,0}, //...
    };

   double test_root2[][2] = { {-2,1}, {1.0,} ,{-1.,2.},{,}, {sqrt(2),-sqrt(2)}, //... 
   }

 //check some 2nd order polynomes

 //3rd order


 // n-th order for different powers with known roots

 // measure performs time

  //time t1 = clock();
  for (int i=0; i<1000000;++i){
    // int r = setPoly(&rs,randomdata,n);
     //time t1 = clock();
     double x =findOneRoot_Gaeffe(&st);
     //time t2 = clock();  
     double x =findOneRoot_Other(&st);
      //time t3 = clock();  //sum times and comapare it
     //....
  } 

//comparison results

}

