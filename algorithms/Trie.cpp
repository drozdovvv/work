#include <iostream>
#include <list>
#include <iterator>

using namespace std;

struct element{
    char cyfra;
    string imie="-";
    list < element* > lista;
};

int main(){
    unsigned int N,i;
    string liczba, im;
    char operacja;
    bool znal=false;
    element * pierwszy_elem = new element;
    element * wsk = new element;

    ios_base::sync_with_stdio(false);

    cin>> N;
    while( N>0 ){
        cin>> operacja;
        if( operacja== 'A' ) cin>> liczba >> im;
        if( operacja== 'S' ) cin>> liczba;
        wsk=pierwszy_elem;
        for( i=0; i< liczba.size() ; i++  ){
            for (  std::list<element * >::iterator it = wsk->lista.begin(); it != wsk->lista.end(); ++it ){
                    //cout<< (*it)->cyfra <<"-" << liczba[i]<< "  ";  // zmienia sie co 2
                if ( liczba[i] == (*it)->cyfra ) {
                    wsk=(*it);
                    znal=true;
                    if( i== liczba.size()-1 && operacja== 'A' ) wsk->imie=im;
                    if( i== liczba.size()-1 && operacja== 'S' ) cout << wsk->imie << "\n";
                    break;
                }
            }
            if( znal==false ){
                if( operacja== 'A' ){
                    element * nowy = new element;
                    nowy->cyfra=liczba[i];
                    if(i== liczba.size()-1) nowy->imie=im;
                    wsk->lista.push_back(nowy);
                    wsk=nowy;
                }
                else if( operacja== 'S' ) {
                        cout << "-\n"; i=liczba.size();
                }
            }
            znal=false;
        }

        N--;
    }

    return 0;
}