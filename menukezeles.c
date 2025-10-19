#include "menukezeles.h"
#include "debugmalloc.h"
#include "hibakezeles.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool tetel_bennevan(ElemMenu* pEleje, Menu sUjtetel);
static bool tetel_torles(ElemMenu** pEleje, char* szNev);




/*
 * Egy menü típusú elemrõl eldönti, hogy benne van-e a menütételeket tartalmazó listában.
 * Bemeneti argumentumok:
 *      pEleje: a menütételeket tartalmazó lista
 *      sUjtetel: a vizsgálandó menü típusú elem
 * Visszatérési érték: igaz, ha benne van a listában az elem,
 *                     hamis, ha nincs benne a listában az elem.
*/
static bool tetel_bennevan(ElemMenu* pEleje, Menu sUjtetel){
    ElemMenu* pIterator;
    for(pIterator = pEleje; pIterator !=  NULL; pIterator = pIterator->pKovetkezo){
        if(strcmp(pIterator->sAdat_menu.szTetel_nev, sUjtetel.szTetel_nev) == 0){
            return true;
        }
    }
    return false;
}

/*
 * Beszúr egy menü típusú elemet a menütételeket tartalmazó listának a legelejére.
 * Bemeneti argumentum:
 *      sUjTetel: a beszúrandó menü típusú elem
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: a menütételeket tartalmazó lista
 *              kimenet esetén: az új menütételt is tartalmazó lista
 * Visszatérési érték: nincs
*/
extern void tetel_hozzaad(ElemMenu** pEleje,  Menu sUjTetel){
    ElemMenu* pUj;
    pUj = (ElemMenu*)malloc(sizeof(ElemMenu));
    pUj->sAdat_menu = sUjTetel;
    if(NULL == *pEleje){
        pUj->pKovetkezo = NULL;
    }
    else{
        pUj->pKovetkezo = *pEleje;
    }
    *pEleje = pUj;
}

/*
 * Kitöröl egy menü típusú elemet a menütételeket tartalmazó listából. Azt az elemet törli ki, amelyiknek a tételneve megegyezik a paraméterként kapott tételnévvel.
 * Bemeneti argumentum:
 *      szNev: karaktertömb (amelyik tételnek a neve egyenlõ ezzel a szöveggel az fog törlõdni).
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: a menütételeket tartalmazó lista
 *              kimenet esetén: a törlendő menütételt már nem tartalmazó lista
 * Visszatérési érték: hamis, ha nem sikerült a törlés,
 *                     igaz, ha sikerült a törlés.
 */
static bool tetel_torles(ElemMenu** pEleje, char* szNev){
    ElemMenu* pIterator = *pEleje;
    ElemMenu* pLemarado = NULL;
    while(pIterator != NULL && strcmp(pIterator->sAdat_menu.szTetel_nev, szNev) != 0){
        pLemarado = pIterator;
        pIterator = pIterator->pKovetkezo;

    }
    if(NULL == pIterator){
        return false;
    }
    else if(NULL == pLemarado){
        ElemMenu *pUjeleje = (*pEleje)->pKovetkezo;
        free(*pEleje);
        *pEleje = pUjeleje;

    }
    else{
        pLemarado->pKovetkezo = pIterator->pKovetkezo;
        free(pIterator);

    }
    return true;

}

/*
 * Felszabadítja a menütételeket tartalmazó lista elemeit a memóriából.
 * Bemeneti argumentum:
 *      pEleje: a menütételeket tartalmazó lista
 * Visszatérési érték: nincs
*/
extern void tetel_felszabadit(ElemMenu* pEleje){
    ElemMenu* pIterator = pEleje;
    while(pIterator != NULL){
        ElemMenu* pKov = pIterator->pKovetkezo;
        free(pIterator);
        pIterator = pKov;
    }
}

/*
 * Kilistázza a menütételek nevét és árát szóközzel elválasztva egymás alá a menütételeket tartalmazó listából a konzolra.
 * Bemeneti argumentum:
 *       pEleje: a menütételeket tartalmazó lista
 * Visszatérési érték: nincs
*/
extern void tetel_kiir(ElemMenu* pEleje){
    ElemMenu* pIterator = pEleje;
    while(pIterator != NULL){
        printf("%s  %d\n", pIterator->sAdat_menu.szTetel_nev, pIterator->sAdat_menu.iTetel_ar);
        pIterator = pIterator->pKovetkezo;
    }
}

/*
 * Bekér a felhasználótól egy tételnevet.
 * Bekér a felhasználótól egy egész számot, ami a tétel ára. Ha a felhasználó nem egész számot ad meg, akkor hibaüzenete ír ki a program, és a függvény visszatér.
 * Ezeket az adatokat eltárolja a függvény egy menü típusú elemben.
 * Ha nincs még ilyen nevű tétel a menütételeket tartalmazó listában, akkor a tetel_hozzaad függvény meghívásával hozzáadja a függgvény a menü típusú elemet a menütételeket tartalmazó listához.
 * Ha már van ilyen nevű tétel a menütételeket tartalmazó listában, akkor hibaüzenetet ír ki a program.
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: a menütételeket tartalmazó lista
                kimenet esetén: az új tételt is tartalmazó lista
 * Visszatérési érték: nincs
 */
extern void tetel_hozzaad_felhaszn(ElemMenu** pEleje){
    Menu sMenu;
    printf("\nAdja meg a tetel nevet: ");
    scanf("%s", sMenu.szTetel_nev);
    char szAdat[250];
    printf("\nAdja meg a tetel arat: ");
    scanf("%s", szAdat);
    if(!szam(szAdat) || atoi(szAdat) <= 0){
        printf("\nNem megfelelo formatum\n");
        return;
    }
    else{
        sMenu.iTetel_ar = atoi(szAdat);
    }
    if(!tetel_bennevan(*pEleje, sMenu)){
        tetel_hozzaad(pEleje, sMenu);
    }
    else{
        printf("\nMar van ilyen menutetel felveve\n");
    }

}


/*
 * Bekér a felhasználótól egy tételnek a nevét.
 * A megadott nevű tételt törli a függvény a menütételeket tartalmazó listából a tetel_torles függvény meghívásával. Ha nincs olyan nevű tétel, amit a felhasználó megadott, akkor a program hibaüzenetet ír ki.
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: a menütételeket tartalmazó lista
 *              kimenet esetén: a törlendő tételt már nem tartalmazó lista
 * Visszatérési érték: nincs
 */
extern void tetel_torles_felhaszn(ElemMenu** pEleje){
    printf("\nAdja meg a torolni kivant tetel nevet: ");
    char szNev[250];
    scanf("%s", szNev);
    bool bSikeres_torles = tetel_torles(pEleje, szNev);
    if(!bSikeres_torles){
        printf("\nNem sikerult a torles, nincs ilyen elem");
    }
}
