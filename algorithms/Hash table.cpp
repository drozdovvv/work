#include <iostream>
#include <iterator>
#include <list>

using namespace std;

struct elem{
    string nazwa;
    string miejsce;
};


int main(){

    ios_base::sync_with_stdio(false);

    char operacja;
    string nazwa, miejsce;
    unsigned int N,i,ascii=0,n,s;
    bool znal=false;

    cin>> N;
    n=N;
    std::list<elem> *lista = new std::list<elem>[N];

    while(N>0){
        cin>> operacja;
        ascii=0;
        if( operacja=='A' ){
            cin>> nazwa >> miejsce;
            s=nazwa.size();
            for ( i=0; i<s; i++){
                ascii= (ascii*17) + (int)(nazwa[i]);
            }
            ascii= ascii%n;

            elem nowy;
            nowy.nazwa=nazwa;
            nowy.miejsce=miejsce;
            lista[ascii].push_back(nowy);
        }

        if( operacja=='S'){
            cin>> nazwa;
            s=nazwa.size();
            for ( i=0; i<s; i++){
                ascii= (ascii*17) + (int)(nazwa[i]);
            }
            ascii= ascii%n;
            for ( std::list<elem > :: iterator it = lista[ascii].begin(); it!=lista[ascii].end(); it++){
                if ( (*it).nazwa== nazwa ){
                    cout<< (*it).miejsce<< "\n";
                    znal=true;
                    break;
                }
            }
            if( znal==false ) cout<< "-\n";
            znal= false;
        }

        N--;
    }

    return 0;
}