#include "menuvezerles.h"
#include "asztalkezeles.h"
#include "menukezeles.h"
#include "hibakezeles.h"
#include "debugmalloc.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Kiírja a konzolra a főmenüpontokat, amikbõl a felhasználó válászthat.
 * Bemeneti argumentum: nincs
 * Visszatérési érték: nincs
*/
extern void kiiras_fomenu(){
    printf("\n1. Asztal kezeles\n2. Menu kezelese\n3. Rendeles felvetele\n4. Szamla nyomtatas\n5. Foglaltsagi terkep megjelenitese\n6. Mentes es kilepes\n");
    printf("\nAdja meg a valasztani kivant menupont szamat: ");

}


/*
 * Kiírja az asztalkezeléshez tartozó almenüpontokat a konzolra, amikbõl a felhasználó válászthat.
 * Továbbá beolvas egy egész számot 1 és 4  között a felhasználótól. Hibás bemenet esetén hibaüzenetet ír ki a program, és a függvény visszatér.
 * Az adott menüszám alapján a megfelelő függvényhívásokkal elvégzi a különböző funkciókat az asztalokat tartalmazó listán.
 * Be- és kimeneti argumentum:
 *      pAsztalLista: bemenet esetén: az asztalokat tartalmazó lista
 *                    kimenet esetén: az asztalokat tartalmazó lista a kért funkció végrehajtása után
 * Visszatérési érték: nincs
*/
extern void almenu1(ElemAsztal** pAsztalLista){
    printf("1. Asztal hozzaadasa\n2. Asztal torlese\n3. Asztalfoglalas modositasa\n4. Vissza a fomenure\n");
    printf("\nAdja meg a valasztani kivant almenupont szamat: ");
    int iMenupont = 0;
    char szAdat[250];
    scanf("%s", szAdat);
    if(!szam(szAdat)){
        printf("\nNem megfelelo formatum\n");
        return;
    }
    else{
        iMenupont = atoi(szAdat);
    }
    switch(iMenupont){
        case 1:
            asztal_hozzaad_felhaszn(pAsztalLista);
            break;
        case 2:
            asztal_torles_felhaszn(pAsztalLista);
            break;
        case 3:
            asztal_foglaltsag_felhaszn(*pAsztalLista);
            break;
        case 4:
            break;
        default:
            printf("\nRossz menuszamot adott meg\n");
            break;
    }

}


/*
 * Kiírja a menütételek kezeléséhez tartozó almenüpontokat a konzolra, amikbõl a felhasználó válászthat.
 * Továbbá beolvas egy egész számot 1 és 4  között a felhasználótól. Hibás bemenet esetén hibaüzenetet ír ki a program, és a függvény visszatér.
 * Az adott menüszám alapján a megfelelő függvényhívásokkal elvégzi a különböző funkciókat a menütételeket tartalmazó listán.
 * Be- és kimeneti argumentum:
 *      pMenuLista: bemenet esetén: a menütételeket tartalmazó lista
 *                  kimenet esetén: a menütételeket tartalmazó lista a kért funkció végrehajtása után
 * Visszatérési érték: nincs
*/
extern void almenu2(ElemMenu** pMenuLista){
    printf("1. Tetel hozzaadasa\n2. Tetel torlese\n3. Menu listazasa\n4. Vissza a fomenure\n");
    printf("\nAdja meg a valasztani kivant almenupont szamat: ");
    int iMenupont = 0;
    char szAdat[250];
    scanf("%s", szAdat);
    if(!szam(szAdat)){
        printf("\nNem megfelelo formatum\n");
        return;
    }
    else{
        iMenupont = atoi(szAdat);
    }
    switch(iMenupont){
            case 1:
                tetel_hozzaad_felhaszn(pMenuLista);
                break;
            case 2:
                tetel_torles_felhaszn(pMenuLista);
                break;
            case 3:
                tetel_kiir(*pMenuLista);
                break;
            case 4:
                break;
            default:
                printf("Rossz menuszamot adott meg");
                break;

                }

}

