#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

struct szlak{
    int a;
    int b;
    double prawdopodob;
};

struct szczyt{
    int num;
    double prawdop;
    szczyt * nast;
};

struct porownaj{
    bool operator()(szlak *elem_1, szlak *elem_2){
        return elem_1->prawdopodob < elem_2->prawdopodob;
    }
};

priority_queue<szlak*, vector<szlak*>, porownaj> kolejka;


double znal( szczyt ** tab_szczyt, int i, bool * odw, int m, double odpowiedz ) {

    odw[i]=true;
    m--;
    while( m>0 ){
        szczyt *wsk = tab_szczyt[i];

        while(wsk!=NULL){
            szlak * nowy =new szlak;
            nowy->a=i;
            nowy->b=wsk->num;
            nowy->prawdopodob=wsk->prawdop;
            kolejka.push(nowy);
            wsk=wsk->nast;
        }

        while(!kolejka.empty()){
            if( odw[kolejka.top()->b]==false ){
                odpowiedz*=kolejka.top()->prawdopodob;
                odw[kolejka.top()->b]=true;
                i = kolejka.top()->b;
                kolejka.pop();
                break;
            }
            kolejka.pop();
        }

        m--;
    }
    return odpowiedz;
}


int main()
{
    ios_base::sync_with_stdio(false);

    int m,n;            //M mowi o liczbie szczytow i schronisk, zas N o ilosci szlakow
    int i, a,b;
    double odpowiedz=1, praw;

    cin >> m >> n;

    bool odw[m];
    szczyt ** tab_szczyt = new szczyt*[m];

    for(i=0; i<m; i++){
        odw[i]=false;
        tab_szczyt[i]=NULL;
    }

    for ( i=0; i<n; i++){
        szczyt * elem_a = new szczyt;
        szczyt * elem_b = new szczyt;
        cin>> a >> b >> praw;
        elem_a->num=a;
        elem_b->num=b;
        elem_a->prawdop=praw;
        elem_b->prawdop=praw;
        elem_a->nast=tab_szczyt[b];
        elem_b->nast=tab_szczyt[a];
        tab_szczyt[a]=elem_b;
        tab_szczyt[b]=elem_a;
    }
    odpowiedz = znal( tab_szczyt, 0, odw, m, odpowiedz );

    cout << fixed << setprecision(3)<< odpowiedz;

    return 0;
}