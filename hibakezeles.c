#include "hibakezeles.h"
#include "debugmalloc.h"
#include <stdbool.h>
#include <string.h>

/*
 * Eldönti egy paraméterként kapott sztringrõl, hogy számon kívül van e benne más karakter.
 * Bemeneti argumentum:
 *      szStr: vizsgálandó szöveg
 * Visszatérési érték: igaz, ha nincs a paraméterként kapott szövegben más karakter számokon kívül, egyébként hamis.
*/
extern bool szam(char* szStr){
    for(int i = 0; i < strlen(szStr); i++){
        if(!(szStr[i] - '0' >= 0 && szStr[i] - '0' <= 9)){
            return false;
        }
    }
    return true;
}

