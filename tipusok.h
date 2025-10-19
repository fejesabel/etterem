#ifndef TIPUSOK_H_INCLUDED
#define TIPUSOK_H_INCLUDED
#include <stdbool.h>

typedef struct Koordinata{
    int iX;
    int iY;
}Koordinata;

typedef struct Rendeles{
    char szTetel_nev[250];
    int iDb;
}Rendeles;

typedef struct ElemRendeles{
    Rendeles sAdat_rendeles;
    struct ElemRendeles* pKovetkezo;
}ElemRendeles;

typedef struct Asztal{
    Koordinata sAdat_koordinata;
    bool bFoglalt;
    int iFeroszam;
    ElemRendeles* pRendeles;
}Asztal;


typedef struct ElemAsztal{
    Asztal sAdat_asztal;
    struct ElemAsztal* pKovetkezo;
}ElemAsztal;


typedef struct Menu{
    char szTetel_nev[250];
    int iTetel_ar;
}Menu;

typedef struct ElemMenu{
    Menu sAdat_menu;
    struct ElemMenu* pKovetkezo;
}ElemMenu;




#endif // TIPUSOK_H_INCLUDED
