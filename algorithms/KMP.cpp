#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include<stdlib.h>
#include <string>
# include <vector>

using namespace std;

struct P{
    char znak;
    int cyfra;
};


int main(){
    string szablon="",tekst="";         //a - oznacza wystapienie malej litery,
                                        //A - oznacza wystapienie duzej litery,
                                        //. - oznacza wystapienie jednego z nastepujacych znakow interpunkcyjnych: kropki, znaku zapytania, wykrzyknika, przecinka, srednika, dwukropka lub myslnika.
                                        //0 - oznacza wystapienie cyfry.
    bool znal=false;
    int i, t_size, s_size;

    getline (cin,szablon);
    getline (cin,tekst);

    s_size=szablon.size();
    t_size=tekst.size();

    for( i=0; i<t_size; i++){
        if ( tekst[i]>=65 && tekst[i]<=90 )  tekst[i]='A';
        else if ( tekst[i]>=97 && tekst[i]<=122 )  tekst[i]='a';
        else if ( tekst[i]>=48 && tekst[i]<=57 )  tekst[i]='0';
        else if ( tekst[i]==46 || tekst[i]==63 ||tekst[i]==33 ||tekst[i]==44 ||tekst[i]==59 ||tekst[i]==58 ||tekst[i]==45 )  tekst[i]='.';
    }


    P pf[s_size];

    for ( i=0; i<s_size;i++){
        pf[i].znak=szablon[i];
    }

    pf[0].cyfra = 0;

    for (int k = 0, i = 1; i < s_size; i++ ) {
		while ((k > 0) && (szablon[i] != szablon[k]))
			k = pf[k-1].cyfra;
		if (szablon[i] == szablon[k])
			k++;
		pf[i].cyfra = k;
	}

	for (int k = 0, i = 0; i < t_size; i++) {
		while ((k > 0) && (szablon[k] != tekst[i]))
			k = pf[k-1].cyfra;
		if (szablon[k] == tekst[i])
			k++;
		if (k == s_size){
            znal=true;
            break;
		}
	}

    if( znal==false ) cout<<"N";
    if( znal==true) cout<<"T";

    return 0;
}