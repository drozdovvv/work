#include <iostream>
#include <cmath>

using namespace std;
/*
double P(int i, int j){
return (i+2)/j*j-20;
}
*/

int zwroc_max( int zm, int n, int index ){
     for(int i=0;i<n;i++){
            if( i==0 &&  P(i,zm-1) >= P(i+1,zm-1)  ){  //sprawdzenie pierwszych 2 elem
                index=i;
                i=n;
            }
            if( i>0 && i<n-1 && P(i,zm-1) >= P(i-1,zm-1) && P(i,zm-1) >= P(i+1,zm-1) ){
                index=i;
                i=n;
            }
            if(i==n-1 &&  P(i,zm-1) >= P(i-1,zm-1)){   //sprawdzenie ostatnich 2 elem
                index=i;
                i=n;
            }
        }

return index;

}

int main()
{
    int n, m;      //wymiary mapy
    //double max=0;
    int ind,zm, a,b,pom;
    bool x=false;

    ios_base::sync_with_stdio(false);

    cin >> n >> m ;

    zm=(int)(m/2);
    a=0;
    b=m;


    if(n==1 && m==1){
        cout << (int)P(0,0);
        return 0;
    }

    if( n>=4 && m>=4 && P((int)n/2-1, (int)m/2-1) >= P((int)n/2-1, (int)m/2-2) &&  P((int)n/2-1, (int)m/2-1) >= P((int)n/2-1, (int)m/2) && P((int)n/2-1, (int)m/2-1) >= P((int)n/2-2, (int)m/2-1) && P((int)n/2-1, (int)m/2-1) >= P((int)n/2, (int)m/2-1) ){
        cout<<(int) P((int)n/2-1, (int)m/2-1);
        return 0;
    }

    if(m==1 && n>1){        // wertikalnaja karta,meniajem, popadajem w sled if
        pom=m;
        m=n;
        n=pom;
    }

    if(n==1){

            if(m==2){
                if( P(0,0) >= P(0,1)){ cout<<(int) P(0,0); return 0; }
                else { cout<< (int)P(0,1); return 0;}
            }

        while(x==false){

            if(zm==m){
                if( P(0, m-1) >= P(0, m-2) ){
                    cout <<(int) P(0, m-1);
                    return 0;
                }
                if( P(0, m-2) >= P(0, m-1) ){
                    cout << (int)P(0, m-2);
                    return 0;
                }
            }


            if(zm==1){
                if( P(0, 0) >= P(0, 1) ){
                    cout << (int)P(0, 0);
                    return 0;
                }
                if( P(0, 1) >= P(0, 0) ){
                    cout << (int)P(0, 1);
                    return 0;
                }
            }


            if( P(0, zm-1) >= P(0, zm)  && P(0, zm-1) >= P(0, zm-2) ){  //sprawdzenie
                cout << (int)P(0, zm-1);
                return 0;
            }

            else{                                //zmniejszenie zakresu
                if( P(0, zm-1) > P(0, zm) ) {
                   b= zm;
                   zm=zm- ceil((b-a)/2);
                }
                else {
                     a=zm;
                     zm= zm+ ceil((b-a)/2);
                }
            }
        }
    }





    else{


        while(x==false){

                ind= zwroc_max(zm,n,0);

            if(zm==m && ind==0){
                if( P(ind, m-1) >= P(ind, m-2) && P(ind, m-1) >= P(ind+1, m-1) ){
                    cout <<(int) P(ind, m-1);
                    return 0;
                }
            }

            if(zm==m && ind==n-1){
                if( P(ind, m-1) >= P(ind, m-2) && P(ind, m-1) >= P(ind-1, m-1) ){
                    cout << (int)P(ind, m-1);
                    return 0;
                }
            }

            if(zm==1 && ind==0){
                if( P(ind, 0) >= P(ind, 1) && P(ind, 0) >= P(ind+1, 0) ){
                    cout << (int)P(ind, 0);
                    return 0;
                }
            }

            if(zm==1 && ind==n-1){
                if( P(ind, 0) >= P(ind, 1) && P(ind, 0) >= P(ind-1, 0) ){
                    cout <<(int) P(ind, 0);
                    return 0;
                }
            }




            if(zm==m){
                if( P(ind, m-1) >= P(ind, m-2) ){
                    cout << (int)P(ind, m-1);
                    return 0;
                }
                if( P(ind, m-2) >= P(ind, m-1) ){
                    cout << (int)P(ind, m-2);
                    return 0;
                }
            }


            if(zm==1){
                if( P(ind, 0) >= P(ind, 1) ){
                    cout << (int)P(ind, 0);
                    return 0;
                }
                if( P(ind, 1) >= P(ind, 0) ){
                    cout << (int)P(ind, 1);
                    return 0;
                }
            }



            if( P(ind, zm-1) >= P(ind, zm)  && P(ind, zm-1) >= P(ind, zm-2) ){  //sprawdzenie
                cout << (int)P(ind, zm-1);
                return 0;
            }

            else{                                //zmniejszenie zakresu
                if( P(ind, zm-1) > P(ind, zm) ) {
                   b= zm;
                   zm=zm- ceil((b-a)/2);
                }
                else {
                     a=zm;
                     zm= zm+ ceil((b-a)/2);
                }
            }
        }



    }


    return 0;
}