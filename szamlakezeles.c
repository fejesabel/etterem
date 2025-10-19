#include "szamlakezeles.h"
#include "debugmalloc.h"
#include "hibakezeles.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Bek�r a felhaszn�l�t�l egy koordin�ta t�pus� elemet. Ha nem eg�sz sz�mot ad meg a koordin�ta �rt�keinek a felhaszn�l�, akkor hiba�zenetet �r ki a program, �s a f�ggv�ny visszat�r.
 * Kilist�zza a bek�rt koordin�t�j� asztalhoz tartoz� rendel�seket �s a hozz�juk tartoz� �rakat. V�g�l ki�rja a fizetend� v�g�sszeget.
 * Bemeneti argumentum:
 *       pEleje_asztal: az asztalokat tartalmaz� lista
 *       pEleje_menu: a men�t�teleket tartalmaz� lista
 * Visszat�r�si �rt�k: nincs
*/
extern void kiir_szamla(ElemAsztal* pEleje_asztal, ElemMenu* pEleje_menu){
    Koordinata sKoordinata;
    char szAdat[250];
    printf("\nAdja meg a szamlazni kivant asztal elhelyezkedeset\n");
    printf("Sorszama: ");
    scanf("%s", szAdat);
    if(!szam(szAdat) || atoi(szAdat) <= 0){
        printf("\n\nNem megfelelo formatum\n");
        return;
    }
    else{
        sKoordinata.iX = atoi(szAdat);
    }
    printf("Oszlopszama: ");
    scanf("%s", szAdat);
    if(!szam(szAdat) || atoi(szAdat) <= 0){
        printf("\n\nNem megfelelo formatum\n");
        return;
    }
    else{
        sKoordinata.iY = atoi(szAdat);
    }
    ElemAsztal* pIterator_asztal = pEleje_asztal;
    while(pIterator_asztal != NULL && (pIterator_asztal->sAdat_asztal.sAdat_koordinata.iX != sKoordinata.iX || pIterator_asztal->sAdat_asztal.sAdat_koordinata.iY != sKoordinata.iY)){
        pIterator_asztal = pIterator_asztal->pKovetkezo;
    }
    if(NULL == pIterator_asztal){
        printf("\nNincs ilyen asztal\n");
    }
    else{
        if(NULL == pIterator_asztal->sAdat_asztal.pRendeles){
            printf("\nAz adott asztalhoz nem tartozik rendeles\n\n");
        }
        else{
            printf("Az adott asztalhoz tartozo szamla:\n");
            ElemRendeles* pIterator_rendeles = pIterator_asztal->sAdat_asztal.pRendeles;
            int iOsszeg = 0;
            while(pIterator_rendeles != NULL){
                int iAr = 0;
                ElemMenu* pIterator_menu = pEleje_menu;
                while(pIterator_menu != NULL){
                    if(strcmp(pIterator_menu->sAdat_menu.szTetel_nev, pIterator_rendeles->sAdat_rendeles.szTetel_nev) == 0){
                        iAr = pIterator_menu->sAdat_menu.iTetel_ar;
                        break;
                    }
                    pIterator_menu = pIterator_menu->pKovetkezo;
                }
                printf("%dx %s %d Ft\n", pIterator_rendeles->sAdat_rendeles.iDb, pIterator_rendeles->sAdat_rendeles.szTetel_nev, iAr);
                iOsszeg += pIterator_rendeles->sAdat_rendeles.iDb*iAr;
                pIterator_rendeles = pIterator_rendeles->pKovetkezo;
            }
            printf("Vegosszeg: %d Ft\n\n", iOsszeg);

        }


    }
}
