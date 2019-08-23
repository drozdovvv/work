#include <iostream>

using namespace std;

struct elem{
    int liczba;
    double wspolszynnik;
    string pseudonim;
    elem * praw=NULL;
    elem * lew=NULL;
    elem * liczba_nast=NULL;
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

void search_and_delete(elem * pom){
    elem * p = new elem;

    if(pom->lew==NULL && pom->praw==NULL){  // jest lisciem
        if(popszedni_sciezka->lew==pom) popszedni_sciezka->lew=NULL;
        else                            popszedni_sciezka->praw=NULL;
    }

    else if( pom->lew!=NULL && pom->praw==NULL ){  // ma tylko lewego syna
        if(popszedni_sciezka->lew==pom) popszedni_sciezka->lew=pom->lew;
        else                            popszedni_sciezka->praw=pom->lew;
    }

    else if( pom->lew==NULL && pom->praw!=NULL ){  // ma tylko prawego syna
        if(popszedni_sciezka->lew==pom) popszedni_sciezka->lew=pom->praw;
        else                            popszedni_sciezka->praw=pom->praw;
    }

    else {  // ma 2 syna
        p=pom->lew;
        if(p->praw==NULL){
            if(popszedni_sciezka->lew==pom) popszedni_sciezka->lew=pom->lew;
            else                            popszedni_sciezka->praw=pom->lew;

            p->praw=pom->praw;
        }
        else{
            while(p->praw!=NULL){
                popszedni=p;
                p=p->praw;
            }
            if(p->lew!=NULL)    popszedni->praw=p->lew;
            else                popszedni->praw=NULL;

            if(popszedni_sciezka->lew==pom) popszedni_sciezka->lew=p;
            else                            popszedni_sciezka->praw=p;

            p->lew=pom->lew;
            p->praw=pom->praw;
        }

    }
}

void Delete(int B, double F){
            double max;
            pom=Search(B);
            if( pom->liczba!=B ) cout<<"-\n";
            else if ( pom->liczba==B && pom->liczba_nast==NULL ){
                if (pom->wspolszynnik>=F){
                        cout<<pom->pseudonim<<"\n";
                        search_and_delete(pom);

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
                    if(findelem==pom){ // pierwszyj elem sciezki
                        if(popszedni_sciezka->lew==pom) popszedni_sciezka->lew=pom->liczba_nast;
                        else                            popszedni_sciezka->praw=pom->liczba_nast;

                        pom->liczba_nast->lew=pom->lew;
                        pom->liczba_nast->praw=pom->praw;
                    }
                    else if( findelem->liczba_nast==NULL){  // ostatni elem sciezki
                        popszedni_max->liczba_nast=NULL;
                    }
                    else{                                   // elem w srodku sciezki
                        popszedni_max->liczba_nast=findelem->liczba_nast;
                    }

                }
                else cout<<"-\n";
            }
}



int main(){
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
                cin >> X >> Y >> nowy->liczba >> nowy->pseudonim;
                nowy->wspolszynnik = (X/5)*(Y/1000);
                //cout<< nowy->wspolszynnik<<endl;
                korzen->lew=nowy;
            }

            // istnije -> tworzenie + search
            else{
                elem * nowy = new elem;
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
            }

        }


        else if ( operacja=='S'){
            cin>> B>> F;
            if (korzen->lew==NULL) cout<<"-\n";
            else {
                Delete(B,F);
            }
        }

        if ( operacja=='S' || operacja=='A' )
            N--;
    }

    return 0;
}