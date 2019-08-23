#include <iostream>
using namespace std;


struct bitkoin{
  int num;
  double waga;
  bitkoin * next;
};

void dijkstra(int x, bool * odw, double * d, bitkoin ** sasiedzi){
    int i, ind;
    bool wszystko_odwirdzono=true;
    double max=-1;

    for(i=0; i<x; i++){
        if ( d[i]>max && odw[i]==false){
            max=d[i];
            ind=i;
        }
        if ( odw[i]==false ) wszystko_odwirdzono= false;
    }

    if( wszystko_odwirdzono==false){
        bitkoin *wsk= sasiedzi[ind];
        while( wsk!=NULL ){
            if( odw[wsk->num]!=true && d[wsk->num] < d[ind]-d[ind]*wsk->waga )
                d[wsk->num]= d[ind]-d[ind]*wsk->waga;
            wsk=wsk->next;
        }
        odw[ind]=true;
        dijkstra(x,odw,d,sasiedzi);
    }

}

int main(){
   int i;
   int N;
   int A,B,M;
   double I,J;
   int x;         // ilosc gield
   cin>>x;
   int bitk[x];   // 0 jesli gielda nie posiada w swojej ofercie BajtCoina
   bool odw[x];
   double d[x];
   bitkoin ** sasiedzi = new bitkoin*[x];

   for(i=0; i<x;i++){
       cin >> bitk[i];
       odw[i]= false;
       d[i]=0;
   }

   cin>> N;

   for(i=0; i<N; i++){
       cin>> A >>B;
       cin>> I >> J;

       bitkoin * a= new bitkoin;
       bitkoin * b= new bitkoin;

       a->num=A;
       a->next=sasiedzi[B];
       a->waga=J;
       b->num=B;
       b->next=sasiedzi[A];
       b->waga=I;

       sasiedzi[A]=b;
       sasiedzi[B]=a;

   }
   cin>>M;
   d[M]=100000;
   dijkstra(x,odw,d,sasiedzi);

   for (i=0;i<x;i++){
       odw[i]=false;
       if(bitk[i]==1)
          d[i]= d[i]*0.2+d[i];
       else
          d[i]=0;
   }
   d[M]=100000;
   dijkstra(x,odw,d,sasiedzi);

   bitkoin *pom, *p;
   for(int i=0; i<x; i++){
            pom=sasiedzi[i];
            while(pom!=NULL) {
                    p=pom;
                    pom=pom->next;
                    delete p;
            }
    }

    delete [] sasiedzi;

   cout<< d[M];

    return 0;
}