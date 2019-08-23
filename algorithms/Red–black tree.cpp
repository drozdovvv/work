#include <iostream>

using namespace std;

struct elem{
    int liczba;
    double wspolszynnik;
    string pseudonim;
    bool kolor;                                        // 0-czarne 1-czerwone
    elem * praw=NULL;
    elem * lew=NULL;
    elem * liczba_nast=NULL;
    elem * ojciec=NULL;
};

            elem * wsk = new elem;
            elem * pom = new elem;
            elem * popszedni = new elem;
            elem * popszedni_sciezka = new elem;
            elem * popszedni_max = new elem;
            // korzen - element pusty
            elem * korzen = new elem;


elem * Search( int liczbanowelem ){
            popszedni_sciezka=korzen;
            wsk=korzen->lew;
            bool znal=false;
            while(znal!=true){
                    if(wsk->liczba > liczbanowelem){
                            if(wsk->lew!=NULL){
                                    popszedni_sciezka=wsk;
                                    wsk=wsk->lew;
                            }
                            else {
                                    return wsk;
                                    znal=true;
                            }
                    }
                    else if(wsk->liczba < liczbanowelem){
                            if(wsk->praw!=NULL){
                                    popszedni_sciezka=wsk;
                                    wsk=wsk->praw;
                            }
                            else {
                                    return wsk;
                                    znal=true;
                            }
                    }
                    else if(wsk->liczba == liczbanowelem){
                                    return wsk;
                                    znal=true;
                    }
            }

}


int rotation( elem * nowy ){
    elem * ppom = new elem;
    ppom=nowy->ojciec;
    if(ppom->kolor==0) return 0;

    //1 przyp
    else if( ppom->ojciec->lew!=NULL && ppom->ojciec->lew->kolor==1 && ppom->ojciec->praw!=NULL && ppom->ojciec->praw->kolor==1 ){
        ppom->ojciec->lew->kolor=0;
        ppom->ojciec->praw->kolor=0;
        ppom->ojciec->kolor=1;

        if(korzen->lew==ppom->ojciec){
            ppom->ojciec->kolor=0;
            return 0;
        }
        else rotation( ppom->ojciec );
    }

    //2 przyp
    else if( ppom->ojciec->lew!=NULL && ppom->ojciec->lew->kolor==1 && ( ppom->ojciec->praw==NULL || ppom->ojciec->praw->kolor==0 )  && ppom->praw==nowy ){              //Wujek C jest czarny, a wezel X jest prawym dzieckiem wezla B
        if(nowy->lew!=NULL){
            ppom->praw=nowy->lew;
            nowy->lew->ojciec=ppom;
        }
        else ppom->praw=NULL;

        nowy->ojciec=ppom->ojciec;
        nowy->ojciec->lew=nowy;
        ppom->ojciec=nowy;
        nowy->lew=ppom;

        rotation(ppom);
    }
    else if( ppom->ojciec->praw!=NULL && ppom->ojciec->praw->kolor==1 && ( ppom->ojciec->lew==NULL || ppom->ojciec->lew->kolor==0 ) && ppom->lew==nowy ){                 //przypadek lustrzany: wujek B jest czarny, a X jest lewym dzieckiem wezla C
        if(nowy->praw!=NULL){
            ppom->lew=nowy->praw;
            nowy->praw->ojciec=ppom;
        }
        else ppom->lew=NULL;

        nowy->ojciec=ppom->ojciec;
        nowy->ojciec->praw=nowy;
        ppom->ojciec=nowy;
        nowy->praw=ppom;

        rotation(ppom);
    }
    //3 przyp
    else if( ppom->ojciec->lew!=NULL && ppom->ojciec->lew->kolor==1 && ( ppom->ojciec->praw==NULL || ppom->ojciec->praw->kolor==0 ) && ppom->lew==nowy ){
            elem * ojoj = new elem;
            ojoj=ppom->ojciec->ojciec;
            if(ppom->praw!=NULL){
                ppom->ojciec->lew=ppom->praw;
                ppom->praw->ojciec=ppom->ojciec;
            }
            else ppom->ojciec->lew=NULL;

            if(ojoj->lew==ppom->ojciec) ojoj->lew=ppom;
            else                        ojoj->praw=ppom;
            ppom->praw=ppom->ojciec;
            ppom->praw->ojciec=ppom;
            ppom->ojciec=ojoj;

            ppom->kolor=0;
            ppom->praw->kolor=1;
    }
    else if( ppom->ojciec->praw!=NULL && ppom->ojciec->praw->kolor==1 && ( ppom->ojciec->lew==NULL || ppom->ojciec->lew->kolor==0 ) && ppom->praw==nowy ){
            elem * ojoj = new elem;
            ojoj=ppom->ojciec->ojciec;
            if(ppom->lew!=NULL){
                ppom->ojciec->praw=ppom->lew;
                ppom->lew->ojciec=ppom->ojciec;
            }
            else ppom->ojciec->praw=NULL;

            if(ojoj->lew==ppom->ojciec) ojoj->lew=ppom;
            else                        ojoj->praw=ppom;
            ppom->lew=ppom->ojciec;
            ppom->lew->ojciec=ppom;
            ppom->ojciec=ojoj;

            ppom->kolor=0;
            ppom->lew->kolor=1;
    }

    return 0;
}


void Search_S(int B, double F){
            double max;
            pom=Search(B);
            if( pom->liczba!=B ) cout<<"-\n";
            else if ( pom->liczba==B && pom->liczba_nast==NULL ){
                if (pom->wspolszynnik>=F){
                        cout<<pom->pseudonim<<"\n";
                }
                else cout<<"-\n";
            }
            else if ( pom->liczba==B && pom->liczba_nast!=NULL ){
                elem * p = new elem;
                elem * findelem = new elem;
                p=pom;
                findelem=pom;
                max=findelem->wspolszynnik;
                while( p->liczba_nast!=NULL ){
                    popszedni=p;
                    p=p->liczba_nast;
                    if(p->wspolszynnik>=max){
                        max=p->wspolszynnik;
                        findelem=p;
                        popszedni_max=popszedni;
                    }
                }
                if(max>=F){
                    cout<< findelem->pseudonim<<"\n";
                }
                else cout<<"-\n";
            }
}



int main(){
    ios_base::sync_with_stdio(false);

    int N,Y,B;        // ilosc operacji
    char operacja;
    double X,F;        //B to ilosc pieniedzy, jakie dokladnie chce wydac nasz student, F - wspolczynniik
    cin>> N;


    while ( N>0 ){
        cin>> operacja;
        if( operacja=='A'){

            //pierwszego elem drzewa BST nie istnieje -> tworzenie
            if( korzen->lew==NULL ){
                elem * nowy = new elem;
                nowy->kolor=0;
                nowy->ojciec=korzen;
                cin >> X >> Y >> nowy->liczba >> nowy->pseudonim;
                nowy->wspolszynnik = (X/5)*(Y/1000);
                //cout<< nowy->wspolszynnik<<endl;
                korzen->lew=nowy;
            }

            // istnije -> tworzenie + search
            else{
                elem * nowy = new elem;
                nowy->kolor=1;
                cin >> X >> Y >> nowy->liczba >> nowy->pseudonim;
                nowy->wspolszynnik = (X/5)*(Y/1000);
                //cout<<nowy->wspolszynnik<<endl;

                pom=Search(nowy->liczba);
                if(pom->liczba > nowy->liczba)       pom->lew=nowy;
                else if(pom->liczba < nowy->liczba)  pom->praw=nowy;
                else if(pom->liczba == nowy->liczba) {
                        while(pom->liczba_nast!=NULL)
                                pom=pom->liczba_nast;
                        pom->liczba_nast=nowy;
                }
                nowy->ojciec=pom;

                if( pom->liczba > nowy->liczba || pom->liczba < nowy->liczba)  rotation(nowy);
            }

        }


        else if ( operacja=='S'){
            cin>> B>> F;
            if (korzen->lew==NULL) cout<<"-\n";
            else {
                Search_S(B,F);
            }
        }

        if ( operacja=='S' || operacja=='A' )
            N--;
    }

    return 0;
}