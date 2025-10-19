#include "tipusok.h"
#include "hibakezeles.h"
#include "menuvezerles.h"
#include "rendeleskezeles.h"
#include "szamlakezeles.h"
#include "asztalkezeles.h"
#include "menukezeles.h"
#include "fajlkezeles.h"
#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


extern int main(int argc, char *argv[])
{
    ElemAsztal* pAsztalLista = NULL;
    ElemMenu* pMenuLista = NULL;
    beolvas_fajlt(&pAsztalLista, &pMenuLista);
    int iMenupont = 0;
    do{
        kiiras_fomenu();
        char szAdat[250];
        scanf("%s", szAdat);
        if(!szam(szAdat)){
            printf("\nNem megfelelo formatum\n\n");
            continue;
        }
        else{
            iMenupont = atoi(szAdat);
        }
        switch(iMenupont){
            case 1:
                almenu1(&pAsztalLista);
                break;
            case 2:
                almenu2(&pMenuLista);
                break;
            case 3:
                rendeles_hozzaad_felhaszn(pAsztalLista, pMenuLista);
                break;
            case 4:
                kiir_szamla(pAsztalLista, pMenuLista);
                break;
            case 5:
                kirajz_terkep(pAsztalLista);
                break;
            case 6:
                break;
            default:
                printf("\nRossz menuszamot adott meg\n\n");
                break;
        }


    }
    while(iMenupont != 6);

    kiir_fajlba(pAsztalLista, pMenuLista);
    asztal_felszabadit(pAsztalLista);
    tetel_felszabadit(pMenuLista);


    return 0;
}
