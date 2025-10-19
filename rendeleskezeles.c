#include "rendeleskezeles.h"
#include "debugmalloc.h"
#include "hibakezeles.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * Felszabad�tja egy asztalhoz tartoz� rendel�seket tartalmaz� lista elemeit a mem�ri�b�l.
 * Bemeneti argumentum:
 *      pEleje: a rendel�seket tartalmaz� lista
 * Visszat�r�si �rt�k: nincs
*/
extern void rendeles_felszabadit(ElemRendeles* pEleje){
    ElemRendeles* pIterator = pEleje;
    while(pIterator != NULL){
        ElemRendeles* pKov = pIterator->pKovetkezo;
        free(pIterator);
        pIterator = pKov;
    }
}

/*
 * Besz�r egy rendel�s t�pus� elemet a rendel�seket tartalmaz� list�nak a legelej�re.
 * Bemeneti argumentum:
 *      sUjRendeles: a besz�rand� rendel�s t�pus� elem
 * Be- �s kimeneti argumentum:
 *      pEleje: bemenet eset�n: a rendel�seket tartalmaz� lista
 *              kimenet eset�n: az �j rendel�st is tartalmaz� lista
 * Visszat�r�si �rt�k: nincs
*/
extern void rendeles_hozzaad(ElemRendeles** pEleje, Rendeles sUjRendeles){
    ElemRendeles* pUj;
    pUj = (ElemRendeles*)malloc(sizeof(ElemRendeles));
    pUj->sAdat_rendeles = sUjRendeles;
    pUj->pKovetkezo = *pEleje;
    *pEleje = pUj;

}


/*
 * Bek�r a felhaszn�l�t�l egy koordin�ta t�pus� elemet. Ha nem eg�sz sz�mot ad meg a koordin�ta �rt�keinek a felhaszn�l�, akkor hiba�zenetet �r ki a program, �s a f�ggv�ny visszat�r.
 * Majd megkeresi a f�ggv�ny ezt a koordin�t�j� asztalt. Ha nincs ilyen asztal, akkor hiba�zenetet �r ki a f�ggv�ny.
 * A f�ggv�ny bek�r a felhaszn�l�t�l egy t�tel nevet a men�b�l. Ha nincs ilyen t�tel a men�t�telek k�z�tt, akkot hiba�zenetet �r ki a f�ggv�ny.
 * A f�ggv�ny bek�r a felhaszn�l�t�l egy eg�sz sz�mot, ami a t�tel darabsz�ma. Ha nem eg�sz sz�mot ad meg a felhaszn�l�, akkor hiba�zenetet �r ki a f�ggv�ny, �s visszat�r.
 * A rendeles_hozzaad f�ggv�ny megh�v�s�val hozz�adja a f�ggv�ny az adott asztalhoz tartoz� rendel�sekhez a rendel�st.
 * Bemeneti argumentum:
 *      pEleje_asztal: az asztalokat tartalmaz� lista
 *      pEleje_menu: a men�t�teleket tartalmaz� lista
 * Visszat�r�si �rt�k: nincs
 */
extern void rendeles_hozzaad_felhaszn(ElemAsztal* pEleje_asztal, ElemMenu* pEleje_menu){
    Koordinata sKoordinata;
    char szAdat[250];
    printf("\nAdja meg az asztal elhelyezkedeset\n");
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
        Rendeles sRendeles;
        printf("\nAdja meg a menubol a tetel nevet: ");
        scanf("%s", sRendeles.szTetel_nev);
        ElemMenu* pIterator_menu = pEleje_menu;
        while(pIterator_menu != NULL && strcmp(pIterator_menu->sAdat_menu.szTetel_nev, sRendeles.szTetel_nev) != 0){
            pIterator_menu = pIterator_menu->pKovetkezo;
        }
        if(NULL == pIterator_menu){
            printf("\nNincs ilyen tetel a menuben\n");
        }
        else{
            printf("\nAdja meg a tetel darabszamat: " );
            char szAdat[250];
            scanf("%s", szAdat);
            if(!szam(szAdat) || atoi(szAdat) <= 0){
                printf("\nNem megfelelo formatum");
            }
            else{
                sRendeles.iDb = atoi(szAdat);
            }
            rendeles_hozzaad(&pIterator_asztal->sAdat_asztal.pRendeles, sRendeles);
        }

    }


}
