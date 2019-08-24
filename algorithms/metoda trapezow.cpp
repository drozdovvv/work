#include <iostream>
#include <math.h>               //M_PI
#include <cstdlib>

using namespace std;



int main(){

    double h,ha,hb,ab=0,p;
    cin>>h;
    for ( double i=0.0; i<h; i+=0.00001 ){
        if( i+0.00001<=h ){
            ha= pow(r(i),2);
            hb= pow(r(i+0.00001),2);
            ab+=(ha+hb);
        }
    }
    p=(M_PI*0.00001)/2;
    ab=ab*p;

    cout<< round(ab);
    return 0;
}