#include "fajlkezeles.h"
#include "asztalkezeles.h"
#include "menukezeles.h"
#include "debugmalloc.h"
#include "rendeleskezeles.h"
#include <stdio.h>
#include <string.h>

static void sortores_torles(char* szSzo);


/*
 * Kiírja a listákat és a hozzájuk tartozó adatokat az etterem.txt fájlba.
 * Bemeneti argumentumok:
 *      pEleje_asztal: az asztalokat tartalmazó lista
 *      pEleje_menu: a menütételeket tartalmazó lista
 * Visszatérési érték: nincs
 */
extern void kiir_fajlba(ElemAsztal* pEleje_asztal, ElemMenu* pEleje_menu){
    FILE* pFp;
    pFp = fopen("etterem.txt", "w");
    if(NULL != pFp){
        ElemAsztal* pIterator_asztal;
        for(pIterator_asztal = pEleje_asztal; pIterator_asztal != NULL; pIterator_asztal = pIterator_asztal->pKovetkezo){
            fprintf(pFp, "%d\n", pIterator_asztal->sAdat_asztal.sAdat_koordinata.iX);
            fprintf(pFp, "%d\n",pIterator_asztal->sAdat_asztal.sAdat_koordinata.iX);
            fprintf(pFp, "%s\n", pIterator_asztal->sAdat_asztal.bFoglalt ? "T" : "F");
            fprintf(pFp, "%d\n", pIterator_asztal->sAdat_asztal.iFeroszam);
            ElemRendeles* pIterator_rendeles;
            for(pIterator_rendeles = pIterator_asztal->sAdat_asztal.pRendeles; pIterator_rendeles != NULL; pIterator_rendeles = pIterator_rendeles->pKovetkezo){
                fprintf(pFp, "%d\n", pIterator_rendeles->sAdat_rendeles.iDb);
                fprintf(pFp, "%s\n", pIterator_rendeles->sAdat_rendeles.szTetel_nev);
            }
            fprintf(pFp, ".\n");


        }
        fprintf(pFp, "!\n");
        ElemMenu* pIterator_menu;
        for(pIterator_menu = pEleje_menu; pIterator_menu != NULL; pIterator_menu = pIterator_menu->pKovetkezo){
            fprintf(pFp, "%s\n", pIterator_menu->sAdat_menu.szTetel_nev);
            fprintf(pFp, "%d\n", pIterator_menu->sAdat_menu.iTetel_ar);
        }
        fclose(pFp);
    }
    else{
        perror("Nem sikerult megnyitni a fajlt");
    }
}
/*
 * Kitörli egy szövegből a '\n' karaktert.
 * Be- és kimeneti argumentum:
 *      szSzo: bemenet esetén: karaktertömb, amelyből törölni kívánja a felhasználó a '\n'-t.
 *             kimenet esetén: karaktertömb, amely már nem tartalmazza a '\n' karakter.
 * Visszatérési érték: nincs
 */
static void sortores_torles(char* szSzo){
    if(szSzo[strlen(szSzo)- 1] == '\n'){
        szSzo[strlen(szSzo)- 1] = '\0';
    }
}

/*
 * Beolvassa az etterem.txt fájlból az adatokat a megfelelő láncolt listákba.
 * Be- és kimeneti argumentum:
 *       pEleje_asztal: bemenet esetén: üres láncolt lista
 *                      kimenet esetén: az asztalokat tartalmazó lista
 *       pEleje_menu: bemenet esetén: üres láncolt lista
 *                    kimenet esetén: a menütételeket tartalmazó lista
 * Visszatérési érték: nincs
 */
extern void beolvas_fajlt(ElemAsztal** pEleje_asztal, ElemMenu** pEleje_menu){
    FILE* pFp;
    pFp = fopen("etterem.txt", "r");
    if(NULL != pFp){
        char szSor [250];
        fgets(szSor, 250, pFp);
        sortores_torles(szSor);
        while(szSor[0] != '!'){
            Koordinata sKoordinata;
            sKoordinata.iX = atoi(szSor);
            fgets(szSor, 250, pFp);
            sortores_torles(szSor);
            sKoordinata.iY = atoi(szSor);
            Asztal sAsztal;
            sAsztal.sAdat_koordinata = sKoordinata;
            fgets(szSor, 250, pFp);
            sortores_torles(szSor);
            if(szSor[0] == 'T'){
                sAsztal.bFoglalt = true;
            }
            else{
                sAsztal.bFoglalt = false;
            }
            fgets(szSor, 250, pFp);
            sortores_torles(szSor);
            sAsztal.iFeroszam = atoi(szSor);

            fgets(szSor, 250, pFp);
            sAsztal.pRendeles = NULL;
            while(szSor[0] != '.'){

                Rendeles sRendeles_adat;
                sRendeles_adat.iDb = atoi(szSor);
                fgets(szSor, 250, pFp);
                sortores_torles(szSor);
                strcpy(sRendeles_adat.szTetel_nev, szSor);
                rendeles_hozzaad(&sAsztal.pRendeles, sRendeles_adat);
                fgets(szSor, 250, pFp);
                sortores_torles(szSor);
            }
            asztal_hozzaad(pEleje_asztal, sAsztal);

            fgets(szSor, 250, pFp);
            sortores_torles(szSor);

        }
        while(NULL != fgets(szSor, 250, pFp)){
            sortores_torles(szSor);
            Menu sMenu_adat;
            strcpy(sMenu_adat.szTetel_nev, szSor);
            fgets(szSor, 250, pFp);
            sortores_torles(szSor);
            sMenu_adat.iTetel_ar = atoi(szSor);
            tetel_hozzaad(pEleje_menu, sMenu_adat);
        }

    }
    else{
        perror("Nincs ilyen fajl");
    }
    fclose(pFp);

}
