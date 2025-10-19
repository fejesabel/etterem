#include "hibakezeles.h"
#include "debugmalloc.h"
#include <stdbool.h>
#include <string.h>

/*
 * Eld�nti egy param�terk�nt kapott sztringr�l, hogy sz�mon k�v�l van e benne m�s karakter.
 * Bemeneti argumentum:
 *      szStr: vizsg�land� sz�veg
 * Visszat�r�si �rt�k: igaz, ha nincs a param�terk�nt kapott sz�vegben m�s karakter sz�mokon k�v�l, egy�bk�nt hamis.
*/
extern bool szam(char* szStr){
    for(int i = 0; i < strlen(szStr); i++){
        if(!(szStr[i] - '0' >= 0 && szStr[i] - '0' <= 9)){
            return false;
        }
    }
    return true;
}

