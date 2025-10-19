#include "rendeleskezeles.h"
#include "debugmalloc.h"
#include "hibakezeles.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * Felszabadítja egy asztalhoz tartozó rendeléseket tartalmazó lista elemeit a memóriából.
 * Bemeneti argumentum:
 *      pEleje: a rendeléseket tartalmazó lista
 * Visszatérési érték: nincs
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
 * Beszúr egy rendelés típusú elemet a rendeléseket tartalmazó listának a legelejére.
 * Bemeneti argumentum:
 *      sUjRendeles: a beszúrandó rendelés típusú elem
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: a rendeléseket tartalmazó lista
 *              kimenet esetén: az új rendelést is tartalmazó lista
 * Visszatérési érték: nincs
*/
extern void rendeles_hozzaad(ElemRendeles** pEleje, Rendeles sUjRendeles){
    ElemRendeles* pUj;
    pUj = (ElemRendeles*)malloc(sizeof(ElemRendeles));
    pUj->sAdat_rendeles = sUjRendeles;
    pUj->pKovetkezo = *pEleje;
    *pEleje = pUj;

}


/*
 * Bekér a felhasználótól egy koordináta típusú elemet. Ha nem egész számot ad meg a koordináta értékeinek a felhasználó, akkor hibaüzenetet ír ki a program, és a függvény visszatér.
 * Majd megkeresi a függvény ezt a koordinátájú asztalt. Ha nincs ilyen asztal, akkor hibaüzenetet ír ki a függvény.
 * A függvény bekér a felhasználótól egy tétel nevet a menübõl. Ha nincs ilyen tétel a menütételek között, akkot hibaüzenetet ír ki a függvény.
 * A függvény bekér a felhasználótól egy egész számot, ami a tétel darabszáma. Ha nem egész számot ad meg a felhasználó, akkor hibaüzenetet ír ki a függvény, és visszatér.
 * A rendeles_hozzaad függvény meghívásával hozzáadja a függvény az adott asztalhoz tartozó rendelésekhez a rendelést.
 * Bemeneti argumentum:
 *      pEleje_asztal: az asztalokat tartalmazó lista
 *      pEleje_menu: a menütételeket tartalmazó lista
 * Visszatérési érték: nincs
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
