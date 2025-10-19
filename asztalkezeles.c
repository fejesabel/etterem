#include "asztalkezeles.h"
#include "hibakezeles.h"
#include "debugmalloc.h"
#include "rendeleskezeles.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool asztal_bennevan(ElemAsztal* pEleje, Asztal sUjAsztal);
static bool asztal_torles(ElemAsztal** pEleje, Koordinata sKoordinata);



/*
 * Egy asztal típusú elemrõl eldönti, hogy benne van-e az asztalokat tartalmazó listában.
 * Bemeneti argumentumok:
 *      pEleje: az asztalokat tartalmazó lista
 *      sUjAsztal: a vizsgálandó asztal típusú elem
 * Visszatérési érték: igaz, ha benne van a listában az elem,
 *                     hamis, ha nincs benne a listában az elem.
*/
static bool asztal_bennevan(ElemAsztal* pEleje, Asztal sUjAsztal){
    ElemAsztal* pIterator;
    for(pIterator = pEleje; pIterator != NULL; pIterator = pIterator->pKovetkezo){
        if(pIterator->sAdat_asztal.sAdat_koordinata.iX == sUjAsztal.sAdat_koordinata.iX && pIterator->sAdat_asztal.sAdat_koordinata.iY == sUjAsztal.sAdat_koordinata.iY){
            return true;
        }
    }
    return false;
}
/*
 * Beszúr egy asztal típusú elemet az asztalokat tartalmazó listának a legelejére.
 * Bemeneti argumentum:
 *      sUjAsztal: a beszúrandó asztal típusú elem
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: az asztalokat tartalmazó lista
 *              kimenet esetén: az új asztalt is tartalmazó lista
 * Visszatérési érték: nincs
*/
extern void asztal_hozzaad(ElemAsztal** pEleje, Asztal sUjAsztal){
    ElemAsztal* pUjAsztal;
    pUjAsztal = (ElemAsztal*)malloc(sizeof(ElemAsztal));
    pUjAsztal->sAdat_asztal = sUjAsztal;
    pUjAsztal->pKovetkezo = *pEleje;
    *pEleje = pUjAsztal;
}

/*
 * Kitöröl egy asztal típusú elemet az asztalokat tartalmazó listából. Azt az elemet törli ki, amelyiknek a koordinátája megegyezik a paraméterként kapott koordinátával.
 * Bemeneti argumentum:
 *      sKoordinata: koordináta típusú elem (amelyik asztal koordinátája egyenlõ ezzel a koordinátával az fog törlõdni).
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: az asztalokat tartalmazó lista
 *              kimenet esetén: a törölendő asztalt már nem tartalmazó lista
 * Visszatérési érték: hamis, ha nem sikerült a törlés,
 *                     igaz, ha sikerült a törlés.
 */
static bool asztal_torles(ElemAsztal** pEleje, Koordinata sKoordinata){
    ElemAsztal* pIterator = *pEleje;
    ElemAsztal* pLemarado = NULL;
    while(pIterator != NULL && (pIterator->sAdat_asztal.sAdat_koordinata.iX != sKoordinata.iX || pIterator->sAdat_asztal.sAdat_koordinata.iY != sKoordinata.iY)){
        pLemarado = pIterator;
        pIterator = pIterator->pKovetkezo;

    }
    if(NULL == pIterator){
        return false;
    }
    else if(NULL == pLemarado){
        ElemAsztal *pUjeleje= (*pEleje)->pKovetkezo;
        rendeles_felszabadit((*pEleje)->sAdat_asztal.pRendeles);
        free(*pEleje);
        *pEleje = pUjeleje;

    }
    else{
        pLemarado->pKovetkezo = pIterator->pKovetkezo;
        rendeles_felszabadit(pIterator->sAdat_asztal.pRendeles);
        free(pIterator);

    }
    return true;

}

/*
 * Felszabadítja az asztalokat tartalmazó lista elemeit a memóriából. Továbbá az asztalokat tartalmazó lista elemeihez tartozó rendelések listáját is felszabadítja.
 * Bemeneti argumentum:
 *      pEleje: az asztalokat tartalmazó lista
 * Visszatérési érték: nincs
*/
extern void asztal_felszabadit(ElemAsztal* pEleje){
    ElemAsztal* pIterator_asztal = pEleje;
    while(pIterator_asztal != NULL){
        ElemAsztal* pKov_asztal = pIterator_asztal->pKovetkezo;
        ElemRendeles* pIterator_rendeles = pIterator_asztal->sAdat_asztal.pRendeles;
        while(pIterator_rendeles != NULL){
            ElemRendeles* pKov_rendeles = pIterator_rendeles->pKovetkezo;
            free(pIterator_rendeles);
            pIterator_rendeles = pKov_rendeles;
        }
        free(pIterator_asztal);
        pIterator_asztal = pKov_asztal;
    }
}


/*
 * Bekér a felhasználótól egy koordináta típusú elemet. Ha nem egész számot ad meg a koordináta értékeinek a felhasználó, akkor hibaüzenetet ír ki a program, és a függvény visszatér.
 * Bekér a felhasználótól egy egész számot, ami az asztal férőhelyinek a száma. Ha a felhasználó nem egész számot ad meg, akkor hibaüzenete ír ki a program, és a függvény visszatér.
 * Ezeket az adatokat eltárolja a függvény egy asztal típusú elemben, az asztal típusú elem foglaltságának értékét hamissá állítja, az asztal típusú elem rendeléseit tartalmazó lista első elemére mutató pointert NULL-ra állítja.
 * Ha nincs még ilyen koordinátájú asztal az asztalokat tartalmazó listában, akkor az asztal_hozzaad függvény meghívásával hozzáadja a függgvény az asztal típusú elemet az asztalokat tartalmazó listához.
 * Ha már van ilyen koordinátájú asztal az asztalokat tartalmazó listában, akkor hibaüzenetet ír ki a program.
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: az asztalokat tartalmazó lista
                kimenet esetén: az új asztalt is tartalmazó lista
 * Visszatérési érték: nincs
 */
extern void asztal_hozzaad_felhaszn(ElemAsztal** pEleje){
    Asztal sAsztal;
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
    sAsztal.sAdat_koordinata = sKoordinata;
    printf("\nAdja meg az asztal ferohelyeinek szamat: ");
    scanf("%s", szAdat);
    if(!szam(szAdat) || atoi(szAdat) <= 0){
        printf("\n\nNem megfelo formatum\n");
        return;
    }
    else{
        sAsztal.iFeroszam = atoi(szAdat);
    }
    sAsztal.bFoglalt = false;
    sAsztal.pRendeles = NULL;
    if(!asztal_bennevan(*pEleje, sAsztal)){
        asztal_hozzaad(pEleje, sAsztal);
    }
    else{
        printf("\nMar van ilyen asztal felveve");
    }
}

/*
 * Bekér a felhasználótól egy koordináta típusú elemet. Ha nem egész számot ad meg a koordináta értékeinek a felhasználó, akkor hibaüzenetet ír ki a program, és a függvény visszatér.
 * A megadott koordinátájú asztalt törli a függvény az asztalokat tartalmazó listából az asztal_torles függvény meghívásával. Ha nincs olyan koordinátájú asztal, amit a felhasználó megadott, akkor a program hibaüzenetet ír ki.
 * Be- és kimeneti argumentum:
 *      pEleje: bemenet esetén: az asztalokat tartalmazó lista
                kimenet esetén: a törlendő asztalt már nem tartalmazó lista
 * Visszatérési érték: nincs
 */
extern void asztal_torles_felhaszn(ElemAsztal** pEleje){
    Koordinata sKoordinata;
    char szAdat[250];
    printf("\nAdja meg a torolni kivant asztal elhelyezkedeset\n");
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
    bool bSikeres_torles = asztal_torles(pEleje, sKoordinata);
    if(!bSikeres_torles){
        printf("\nNem sikerult a torles, nincs ilyen asztal");

    }

}
/*
 * Bekér a felhasználótól egy koordináta típusú elemet. Ha nem egész számot ad meg a koordináta értékeinek a felhasználó, akkor hibaüzenetet ír ki a program, és a függvény visszatér.
 * A megadott koordinátájú asztal foglaltságát módosítja a függvény. Ha szabad volt az asztal, akkor foglalt lesz a foglaltsága. Ha foglalt volt az asztal, akkor szabad lesz, és ekkor az asztalhoz tartozó rendelések törlődnek.
 * Bemeneti argumentum:
        pEleje: az asztalokat tartalmazó lista
 * Visszatérési érték: nincs
 */
extern void asztal_foglaltsag_felhaszn(ElemAsztal* pEleje){
    char szAdat[250];
    Koordinata sKoordinata;
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
    ElemAsztal* pIterator;
    for(pIterator = pEleje; pIterator != NULL; pIterator = pIterator->pKovetkezo){
        if(pIterator->sAdat_asztal.sAdat_koordinata.iX == sKoordinata.iX && pIterator->sAdat_asztal.sAdat_koordinata.iY == sKoordinata.iY){
            if(pIterator->sAdat_asztal.bFoglalt){
                pIterator->sAdat_asztal.bFoglalt = false;
                ElemRendeles* pRendeles = pEleje->sAdat_asztal.pRendeles;
                rendeles_felszabadit(pRendeles);
                pEleje->sAdat_asztal.pRendeles = NULL;
            }
            else{
                pIterator->sAdat_asztal.bFoglalt = true;

            }

            break;
        }

    }
    if(NULL == pIterator){
        printf("\nNincs ilyen asztal");
    }


}
/*
 * Kirajzolja a konzolra a foglaltsági térképet. A foglalt asztalokat 'X'-el, a szabad asztalokat 'O'-val rajzolja ki. Ha nincs egy asztal se felvéve, akkor hibaüzenetet ír ki.
 * Bemeneti argumentum:
 *      pEleje: az asztalokat tartalmazó lista
 * Visszatérési érték: nincs
*/
extern void kirajz_terkep(ElemAsztal* pEleje){
    int iMax_x = -2;
    int iMax_y = -2;
    ElemAsztal* pIterator;
    for(pIterator = pEleje; pIterator != NULL; pIterator = pIterator->pKovetkezo){
        if(pIterator->sAdat_asztal.sAdat_koordinata.iX > iMax_x){
            iMax_x = pIterator->sAdat_asztal.sAdat_koordinata.iX;

        }
    }
    for(pIterator = pEleje; pIterator != NULL; pIterator = pIterator->pKovetkezo){
        if(pIterator->sAdat_asztal.sAdat_koordinata.iX == iMax_x){
            if(pIterator->sAdat_asztal.sAdat_koordinata.iY > iMax_y){
                iMax_y = pIterator->sAdat_asztal.sAdat_koordinata.iY;
            }

        }
    }
    for(int i = 1; i <= iMax_y + 2; i++){
        printf("*");
    }
    printf("\n");

     for(int i = 1; i <= iMax_x; i++){
        printf("*");
        for(int j = 1; j <= iMax_y; j++){

            for(pIterator = pEleje; pIterator != NULL && (pIterator->sAdat_asztal.sAdat_koordinata.iX != i || pIterator->sAdat_asztal.sAdat_koordinata.iY != j); pIterator = pIterator->pKovetkezo){
            }
            if(NULL == pIterator){
                printf(" ");
            }
            else if(pIterator->sAdat_asztal.bFoglalt){
                printf("X");
            }
            else{
                printf("O");
            }
        }
        printf("*");
        printf("\n");

    }
    for(int i = 1; i <= iMax_y + 2; i++){
        printf("*");
    }
    printf("\n\n");
    if(iMax_x < 1 && iMax_y < 1){
        printf("\nNincs asztal felveve\n");
    }



}

