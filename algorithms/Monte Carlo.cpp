#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>

using namespace std;


int main(){
    double x,y,pom;
    double a,b;
    double odpow=0.0;
    cin>> x >> y;

    for ( int i=0; i< 50000000; i++ ){
            a=(double) rand()/RAND_MAX;
            b=(double) rand()/RAND_MAX;

            pom = d( a*x , b*y);

            if( pom > 0.0 )  odpow+= pom;
    }

    odpow=odpow/50000000.0;
    cout<< (int)(odpow*x*y);

    return 0;
}